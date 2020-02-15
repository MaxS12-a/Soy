#include "pch.h"
#include "Selector.h"

Selector::Selector(float x, float y, const sf::Vector2f& guiScale, const sf::Vector2f& origin, const sf::Vector2u& windowResolution, 
	const sf::Font& font, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor, bool goBold, const std::string& idleTextureFile, 
	const std::string& pressedTextureFile, const sf::Vector2f& scaleOnHover, sf::Sound& hoverSoundText, sf::Sound& pressedSoundText, 
	sf::Sound& hoverSoundButtons, sf::Sound& pressedSoundButtons, int distCenterToCenter, std::vector<std::string>* options, int baseOption)
	:GuiItem(x, y, guiScale, origin, windowResolution), options(options), option(baseOption), distCenterToCenter(distCenterToCenter)
{
	text = new TextButton(0, 0, (*options)[baseOption], font, charSize, idleColor, hoverColor, guiScale, origin, 
		windowResolution, goBold, hoverSoundText, pressedSoundText);

	buttonL = new SpriteButton(0, 0, idleTextureFile, pressedTextureFile, guiScale, origin, 
		windowResolution, hoverSoundButtons, pressedSoundButtons, scaleOnHover);
	buttonL->setPosition(-distCenterToCenter * guiScale.x, 0);
	buttonR = new SpriteButton(0, 0, idleTextureFile, pressedTextureFile, guiScale, origin,
		windowResolution, hoverSoundButtons, pressedSoundButtons, scaleOnHover);
	buttonL->setPosition(distCenterToCenter * guiScale.x, 0);
	buttonR->setRotation(180);

	setPosition(x, y);
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
	}
	if (buttonR->update(mouseState)) {
		option++;
		if (option == options->size()) option = 0;
		text->setString((*options)[option]);
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
	buttonR->setPosition(distCenterToCenter * guiScale.x, 0);
}

void* Selector::getInfo()
{
	return (void*)&options[option];
}
