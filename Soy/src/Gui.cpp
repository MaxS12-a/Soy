#include "pch.h"
#include "Gui.h"

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

unsigned char Gui::update(const MouseState& mouseState)
{
	ret = 0;

	for (auto i : guiItems)
		if (i.second->update(mouseState))
			ret = i.first;

	return ret;
}

unsigned char Gui::update()
{
	return 0;
}

void Gui::render(sf::RenderTarget* target)
{
	for (auto i : guiItems) target->draw(*i.second);
}

void Gui::addGuiItem(int id, GuiItem* guiItem)
{
	guiItems[id] = guiItem;
}

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

void Gui::addFont(const std::string& fontName, const std::string& fontFile)
{
	fonts[fontName].loadFromFile(fontFile);
}

sf::Font& Gui::getFont(const std::string& fontName)
{
	return fonts[fontName];
}

GuiItem* Gui::getItem(unsigned char id)
{
	return guiItems[id];
}

void Gui::removeItem(unsigned char id)
{
	guiItems.erase(id);
}

void Gui::create(const sf::Vector2u& windowResolution, const sf::Vector2f& guiScale)
{
	for (auto i : guiItems) i.second->create(windowResolution, guiScale);
}
