#include "pch.h"
#include "State.h"

State::State(Game* game, sf::RenderWindow* window)
	: game(game), window(window)
{
}

State::~State()
{
}

void State::updateMousePos()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}
