#pragma once
#include "Selector.h"
#include "GuiSprite.h"
#include "GuiContainer.h"

class Gui
{
public:
	Gui();
	virtual ~Gui();

	unsigned char update();
	unsigned char update(const MouseState& mouseState);

	void render(sf::RenderTarget* target);

	void addGuiItem(int id, GuiItem* guiItem);

	void addSound(const std::string& soundName, const std::string& soundFile);
	sf::Sound& getSound(const std::string& soundName);
	void setVolume(float volume);

	void addFont(const std::string& fontName, const std::string& fontFile);
	sf::Font& getFont(const std::string& fontName);

	GuiItem* getItem(unsigned char id);
	void removeItem(unsigned char id);

	void create(const sf::Vector2u& windowResolution,const sf::Vector2f& guiScale);
private:
	std::map<int, GuiItem*> guiItems;

	std::map<std::string, std::pair<sf::SoundBuffer*, sf::Sound*>> sounds;
	std::map<std::string, sf::Font> fonts;

	unsigned char ret;
};

