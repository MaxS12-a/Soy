#pragma once
#include "Selector.h"
#include "GuiSprite.h"
#include "GuiContainer.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"

// Class used to easely manipulate guiItems.
class Gui
{
public:
	// Constructors & destructors
	Gui();
	virtual ~Gui();

	// GL methods
	unsigned char update(const MouseState& mouseState);

	void render(sf::RenderTarget* target);

	// Item methods
	void create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale);

	void addItem(int id, GuiItem* guiItem);
	void removeItem(unsigned char id);
	GuiItem* getItem(unsigned char id);

	// Sound handlers
	void addSound(const std::string& soundName, const std::string& soundFile);
	sf::Sound& getSound(const std::string& soundName);
	void setVolume(float volume);

	// Font handlers
	void addFont(const std::string& fontName, const std::string& fontFile);
	sf::Font& getFont(const std::string& fontName);	

private:
	std::map<int, GuiItem*> guiItems;

	std::map<std::string, std::pair<sf::SoundBuffer*, sf::Sound*>> sounds;
	std::map<std::string, sf::Font> fonts;

	unsigned char ret;
};

