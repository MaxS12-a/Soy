#include "pch.h"
#include "State.h"

State::State(Game* game, sf::RenderWindow* window)
	: game(game), window(window)
{
}

State::~State()
{
}
