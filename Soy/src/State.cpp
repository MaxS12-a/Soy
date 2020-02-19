#include "pch.h"
#include "State.h"

State::State(StateStuff* stateStuff)
	: stateStuff(stateStuff)
{
}

State::~State()
{
}

void State::updateMouse()
{
	mouseState.mousePosScreen = sf::Mouse::getPosition();
	mouseState.mousePosWindow = sf::Mouse::getPosition(*stateStuff->window);

	if (!mouseState.mousePressedLeft && sf::Mouse::isButtonPressed(sf::Mouse::Left)) mouseState.mouseClickLeft = true;
	else mouseState.mouseClickLeft = false;

	if (!mouseState.mousePressedRight && sf::Mouse::isButtonPressed(sf::Mouse::Right)) mouseState.mouseClickRight = true;
	else mouseState.mouseClickRight = false;

	if (mouseState.mousePressedLeft && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) mouseState.mouseReleasedLeft = true;
	else mouseState.mouseReleasedLeft = false;

	if (mouseState.mousePressedRight && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) mouseState.mouseReleasedRight = true;
	else mouseState.mouseReleasedRight = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) mouseState.mousePressedLeft = true;
	else mouseState.mousePressedLeft = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) mouseState.mousePressedRight = true;
	else mouseState.mousePressedRight = false;


}


StateStuff::Volumes::Volumes(bool muted, float musicVol, float guiVol)
	:muted(muted), musicVol(musicVol), guiVol(guiVol)
{
}

// StateStuff::Volumes
void StateStuff::Volumes::mute() {
	this->muted = !muted;
	if (muted) {
		musicVolUM = musicVol;
		guiVolUM = guiVol;
		musicVol = 0;
		guiVol = 0;
	}
	else {
		musicVol = musicVolUM;
		guiVol = guiVolUM;
	}
}

void StateStuff::Volumes::increaseMusicVol(float vol) {
	musicVol += vol;
	if (musicVol >= 100) musicVol = 100;
	else if (musicVol <= 0) musicVol = 0;
}

void StateStuff::Volumes::increaseGuiVol(float vol) {
	guiVol += vol;
	if (guiVol >= 100) guiVol = 100;
	else if (guiVol <= 0) guiVol = 0;
}
