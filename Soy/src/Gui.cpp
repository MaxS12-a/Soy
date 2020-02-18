#include "pch.h"
#include "Gui.h"

// Constructors & destructors
Gui::Gui()
{
}

Gui::~Gui()
{
	for (auto i : guiItems) delete i.second;

	for (auto i : sounds) {
		delete i.second.first;
		delete i.second.second;
	}
}

// GL methods
unsigned char Gui::update(const MouseState& mouseState)
{
	ret = 0;

	for (auto i : guiItems) {
		if (i.second->update(mouseState))
			ret = i.first;
		if (i.second->update())
			ret = i.first;
	}
	return ret;
}

void Gui::render(sf::RenderTarget* target)
{
	for (auto i : guiItems) target->draw(*i.second);
}

// Item functions
void Gui::create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
{
	for (auto i : guiItems) i.second->create(windowResolution, guiScale);
}


void Gui::addItem(int id, GuiItem* guiItem)
{
	guiItems[id] = guiItem;
}

void Gui::removeItem(unsigned char id)
{
	guiItems.erase(id);
}

GuiItem* Gui::getItem(unsigned char id)
{
	return guiItems[id];
}

// Sound handlers
void Gui::addSound(const std::string& soundName, const std::string& soundFile)
{
	sounds[soundName] = std::pair<sf::SoundBuffer*, sf::Sound*>(new sf::SoundBuffer(), new sf::Sound());
	
	if (!sounds[soundName].first->loadFromFile(soundFile)) LOG_CRITICAL("Could not load {0}", soundFile);
	else sounds[soundName].second->setBuffer(*sounds[soundName].first);
}

sf::Sound& Gui::getSound(const std::string& soundName) {
	return *sounds[soundName].second;
}

void Gui::setVolume(float volume)
{
	for (auto i : sounds)
		i.second.second->setVolume(volume);
}

// Font handlers
void Gui::addFont(const std::string& fontName, const std::string& fontFile)
{
	fonts[fontName].loadFromFile(fontFile);
}

sf::Font& Gui::getFont(const std::string& fontName)
{
	return fonts[fontName];
}