#include "pch.h"
#include "TextButton.h"

// Constructors & destructors
TextButton::TextButton(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale,
	const std::string& name, const sf::Font& font, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor, 
	bool goBold, sf::Sound& hoverSound, sf::Sound& pressedSound)
	: Button(x, y, origin, windowResolution, guiScale, hoverSound, pressedSound), 
	charSize(charSize), goBold(goBold),	colorControler(false)
{
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;

	text.setFont(font);
	text.setString(name);
	text.setFillColor(idleColor);

	create(windowResolution, guiScale);
}

TextButton::~TextButton()
{
}

// GL methods
bool TextButton::update(const MouseState& mouseState)
{
	if (Button::update(mouseState)) return true;

	if (hover && !colorControler) {
		colorControler = true;
		text.setFillColor(hoverColor); 
		if(goBold)
			text.setStyle(sf::Text::Bold);
	}else if(!hover && colorControler) {
		colorControler = false;
		text.setFillColor(idleColor);
		if(goBold)
			text.setStyle(sf::Text::Regular);
	}

	return false;
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text, states);
}

void TextButton::create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
{
	this->windowResolution = windowResolution;
	this->guiScale = guiScale;

	setPosition(x / 1920 * windowResolution.x, y / 1080 * windowResolution.y);

	text.setCharacterSize(charSize * guiScale.y);
	text.setPosition(0, 0);
	text.setOrigin(0, 0);
	text.setPosition(-text.getGlobalBounds().left, -text.getGlobalBounds().top);
	std::pair<int, int> newOrigin = getNewOrigin(origin, std::pair<int, int>(text.getGlobalBounds().width, text.getGlobalBounds().height));
	text.setOrigin(newOrigin.first, newOrigin.second);

	doHitBox();
}

// Specific methods
void TextButton::doHitBox() {
	hitBox = text.getGlobalBounds();
	hitBox.left += getPosition().x;
	hitBox.top += getPosition().y;
}

void TextButton::setString(const std::string& newString)
{
	text.setString(newString);
	create(windowResolution, guiScale);
}

const sf::FloatRect& TextButton::getGlobalBounds()
{
	return hitBox;
}
