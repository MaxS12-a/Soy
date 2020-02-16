#include "pch.h"
#include "Selector.h"

Selector::Selector(float x, float y, const sf::Vector2f& guiScale, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, 
	const sf::Font& font, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor, bool goBold, const std::string& idleTextureFile, 
	const std::string& pressedTextureFile, const sf::Vector2f& scaleOnHover, sf::Sound& hoverSoundText, sf::Sound& pressedSoundText, 
	sf::Sound& hoverSoundButtons, sf::Sound& pressedSoundButtons, int distCenterToCenter, std::vector<std::string>* options, int baseOption)
	:GuiItem(x, y, guiScale, origin, windowResolution), options(options), option(baseOption), distCenterToCenter(distCenterToCenter)
{
	text = new TextButton(0, 0, (*options)[baseOption], font, charSize, idleColor, hoverColor, guiScale, { 0.5, 0.5 },
		windowResolution, goBold, hoverSoundText, pressedSoundText);

	buttonL = new SpriteButton(0, 0, idleTextureFile, pressedTextureFile, guiScale, {0.5, 0.5},
		windowResolution, hoverSoundButtons, pressedSoundButtons, scaleOnHover);

	buttonR = new SpriteButton(0, 0, idleTextureFile, pressedTextureFile, guiScale, { 0.5, 0.5 },
		windowResolution, hoverSoundButtons, pressedSoundButtons, scaleOnHover);
	buttonR->setRotation(180);

	create(windowResolution, guiScale);
}

Selector::~Selector()
{
	delete text;
	delete buttonL;
	delete buttonR;
}

bool Selector::update(const MouseState& mouseState)
{
	if (buttonL->update(mouseState)) {
		option--;
		if (option == -1) option = options->size() - 1;
		text->setString((*options)[option]);
		text->moveHitBox(getPosition().x, getPosition().y);
	}
	if (buttonR->update(mouseState)) {
		option++;
		if (option == options->size()) option = 0;
		text->setString((*options)[option]);
		text->moveHitBox(getPosition().x, getPosition().y);
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

	buttonL->setPosition(-distCenterToCenter * guiScale.x, 0);
	buttonL->doHitBox();
	buttonR->setPosition(distCenterToCenter * guiScale.x, 0);
	buttonR->doHitBox();

	text->moveHitBox(getPosition().x, getPosition().y);
	buttonL->moveHitBox(getPosition().x, getPosition().y);
	buttonR->moveHitBox(getPosition().x, getPosition().y);
}

void* Selector::getInfo()
{
	return (void*)new std::string((*options)[option]);
}
