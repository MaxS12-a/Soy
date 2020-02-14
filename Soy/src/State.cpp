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
