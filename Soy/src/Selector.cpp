#include "pch.h"
#include "Selector.h"

// Constructors & destructors
Selector::Selector(float x, float y, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale,
	int distItI, std::vector<std::string>* options, int baseOption,
	/* Text */
	const sf::Font& font, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& outlineColor, int outlineThickness, sf::Sound* hoverSoundText, sf::Sound* pressedSoundText,
	/* Arrows */
	const std::string& textureFile, const sf::Vector2f& scaleOnHover, sf::Sound* hoverSoundButtons, sf::Sound* pressedSoundButtons)
	:GuiItem(x, y, origin, windowResolution,  guiScale), options(options), option(baseOption), distItI(distItI), hitBoxPos({ 0,0 })
{
	text = new TextButton(0, 0, origin, windowResolution, guiScale, 
		(*options)[baseOption], font, charSize, idleColor, hoverColor,
		outlineColor, outlineThickness, hoverSoundText, pressedSoundText);

	buttonL = new SpriteButton(0, 0, origin, windowResolution, guiScale,
		textureFile, scaleOnHover, hoverSoundButtons, pressedSoundButtons);

	buttonR = new SpriteButton(0, 0, origin, windowResolution, guiScale,
		textureFile, scaleOnHover, hoverSoundButtons, pressedSoundButtons);
	buttonR->setRotation(180);

	create(windowResolution, guiScale);
}

Selector::~Selector()
{
	delete text;
	delete buttonL;
	delete buttonR;
	delete options;
}

// GL methods
bool Selector::update(const MouseState& mouseState)
{
	if (buttonL->update(mouseState)) {
		option--;
		if (option == -1) option = options->size() - 1;
		text->setString((*options)[option]);
		
		doButtons();
	}
	if (buttonR->update(mouseState)) {
		option++;
		if (option == options->size()) option = 0;
		text->setString((*options)[option]);
		
		doButtons();
	}
	if (text->update(mouseState)) return true;

	return false;
}

void Selector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*text, states);
	target.draw(*buttonL, states);
	target.draw(*buttonR, states);
}

void Selector::create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
{
	this->windowResolution = windowResolution;
	this->guiScale = guiScale;

	setPosition(x / 1920 * windowResolution.x, y / 1080 * windowResolution.y);

	text->create(windowResolution, guiScale);
	buttonL->create(windowResolution, guiScale);
	buttonR->create(windowResolution, guiScale);

	doButtons();

	moveHitBox(getPosition().x, getPosition().y);
}

void Selector::doButtons()
{
	text->move((buttonL->getGlobalBounds().width + distItI) * (1 - origin.x * 2), 0);
	text->doHitBox();
	text->moveHitBox(hitBoxPos.x, hitBoxPos.y);

	buttonL->setPosition(text->getGlobalBounds().left - hitBoxPos.x - distItI - buttonL->getGlobalBounds().width * (1 - origin.x), 0);
	buttonL->doHitBox();
	buttonL->moveHitBox(hitBoxPos.x, hitBoxPos.y);

	buttonR->setPosition(text->getGlobalBounds().left - hitBoxPos.x + text->getGlobalBounds().width + distItI + buttonR->getGlobalBounds().width * (1 - origin.x), 0);
	buttonR->doHitBox();
	buttonR->moveHitBox(buttonR->getGlobalBounds().width * (origin.x - 0.5) * 2, 0);
	buttonR->moveHitBox(hitBoxPos.x, hitBoxPos.y);
}

// Specific methods
void Selector::moveHitBox(float x, float y) 
{	
	text->moveHitBox(x, y);
	buttonL->moveHitBox(x, y);
	buttonR->moveHitBox(x, y);
	hitBoxPos.x = x;
	hitBoxPos.y = y;
}

const sf::FloatRect& Selector::getGlobalBounds()
{
	globalBounds = sf::FloatRect(
		sf::Vector2f({ buttonL->getGlobalBounds().left, text->getGlobalBounds().top }),
		sf::Vector2f({ buttonR->getGlobalBounds().left + buttonR->getGlobalBounds().width - buttonL->getGlobalBounds().left ,
			text->getGlobalBounds().height }));
	return globalBounds;
}

void* Selector::getInfo()
{
	return (void*)new std::string((*options)[option]);
}
