#include "pch.h"
#include "Button.h"

Button::Button(float x, float y, const char* bname, 
	const sf::Vector2f& guiScale, Corner corner, const sf::Vector2u& windowResolution, const char* hoverSound, const char* pressedSound)
	: GuiItem(x, y, guiScale, corner, windowResolution), bname(bname), hover(false), pressed(false), ponh(false)
{
	if (hoverSound) {
		hoverSoundB = new sf::SoundBuffer();
		if (!hoverSoundB->loadFromFile(hoverSound)) LOG_CRITICAL("Could not load {0}.", hoverSound);
		else {
			this->hoverSound = new sf::Sound();
			this->hoverSound->setBuffer(*hoverSoundB);
		}
	}
	if (pressedSound) {
		pressedSoundB = new sf::SoundBuffer();
		if (!pressedSoundB->loadFromFile(pressedSound)) LOG_CRITICAL("Could not load {0}.", pressedSound);
		else {
			this->pressedSound = new sf::Sound();
			this->pressedSound->setBuffer(*pressedSoundB);
		}
	}
}

Button::~Button()
{
	int i = 0;
	if (hoverSound) {
		while (hoverSound->getStatus() == sf::Sound::Playing) i++;
		delete hoverSoundB;
		delete hoverSound;
	}
	if (pressedSound) {
		while (pressedSound->getStatus() == sf::Sound::Playing) i++;
		delete pressedSoundB;
		delete pressedSound;
	}
}

bool Button::update(int x, int y, bool press)
{
	if (hitBox.contains(x, y)) { 
		if (!hover && hoverSound) hoverSound->play();
		hover = true; 
		if (!press && ponh) ponh = false;
	}
	else {
		hover = false;
		if(press) ponh = true;
	}

	if (pressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		pressed = false;
		return true;
	}

	if (hover && press && !ponh) {
		if (!pressed && pressedSound) pressedSound->play();
		pressed = true;
	} else pressed = false;

	return false;
}

void Button::setVolume(float volume)
{
	if (hoverSound) hoverSound->setVolume(volume);
	if (pressedSound) pressedSound->setVolume(volume);
}
