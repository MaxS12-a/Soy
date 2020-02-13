#include "pch.h"
#include "TextButton.h"

TextButton::TextButton(float x, float y, const char* bname, 
	const char* fontFile, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor,
	const sf::Vector2f& guiScale, Corner corner, const sf::Vector2u& windowResolution,
	const char* hoverSound = nullptr, const char* pressedSound = nullptr)
	: Button(x, y , bname, guiScale, corner, windowResolution, hoverSound, pressedSound), charSize(charSize)
{
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;

	if(!font.loadFromFile(fontFile)) LOG_CRITICAL("Could not load {0}.", fontFile);

	text.setFont(font);
	text.setString(bname);
	text.setFillColor(idleColor);
	text.setStyle(sf::Text::Regular);

	create(windowResolution, guiScale);
}

bool TextButton::update(int x, int y, bool press)
{
	if (Button::update(x, y, press)) return true;

	if (hover) {
		text.setFillColor(hoverColor); 
		text.setStyle(sf::Text::Bold);
	}
	else if(text.getStyle() == sf::Text::Bold){
		text.setFillColor(idleColor);
		text.setStyle(sf::Text::Regular);
	}

	return false;
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text, states);
}

void TextButton::create(sf::Vector2u windowResolution, sf::Vector2f guiScale)
{
	setPosition(x/1920*windowResolution.x, y/1080*windowResolution.y);

	text.setCharacterSize(charSize * guiScale.y);
	text.setPosition(0, 0);
	text.setOrigin(0, 0);
	text.setPosition(-text.getGlobalBounds().left, -text.getGlobalBounds().top);
	std::pair<int, int> newOrigin = getNewOrigin(corner, std::pair<int, int>(text.getGlobalBounds().width, text.getGlobalBounds().height));
	text.setOrigin(newOrigin.first, newOrigin.second);

	hitBox = sf::FloatRect(text.getGlobalBounds());
	hitBox.left += getPosition().x;
	hitBox.top += getPosition().y;
}