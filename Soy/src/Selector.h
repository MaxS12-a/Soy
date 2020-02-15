#pragma once
#include "TextButton.h"
#include "SpriteButton.h"

class Selector :
	public GuiItem
{
public:
	Selector(float x, float y, const sf::Vector2f& guiScale, const sf::Vector2f& origin, const sf::Vector2u& windowResolution,
		const sf::Font& font, int charSize, const sf::Color& idleColor, const sf::Color& hoverColor, bool goBold,
		const std::string& idleTextureFile, const std::string& pressedTextureFile, const sf::Vector2f& scaleOnHover,
		sf::Sound& hoverSoundText, sf::Sound& pressedSoundText, sf::Sound& hoverSoundButtons, sf::Sound& pressedSoundButtons,
		int distCenterToCenter, std::vector<std::string>* options, int baseOption);
	virtual ~Selector();

	bool update(const MouseState& mouseState);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);

	void* getInfo();

private:
	TextButton* text;
	SpriteButton* buttonL;
	SpriteButton* buttonR;
	std::vector<std::string>* options;
	int option;
	int distCenterToCenter;
};

