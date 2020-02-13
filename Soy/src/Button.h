#pragma once
#include "GuiItem.h"
class Button :
	public GuiItem
{
public:
	Button(float x, float y, const char* bname, const sf::Vector2f& guiScale, Corner corner, const sf::Vector2u& windowResolution,
		const char* hoverSound, const char* pressedSound);
	virtual ~Button();

	virtual bool update(int x, int y, bool press);

	virtual void setVolume(float volume);
protected:
	sf::FloatRect hitBox;

	std::string bname;

	bool hover, pressed, ponh;

	sf::SoundBuffer* hoverSoundB;
	sf::SoundBuffer* pressedSoundB;
	sf::Sound* hoverSound;
	sf::Sound* pressedSound;
};

