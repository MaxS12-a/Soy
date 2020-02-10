#pragma once
#include "SFML/Graphics.hpp"

class Game;

class State
{
public:
	//Constructors
	State(Game* game, sf::RenderWindow* window);
	virtual ~State();

	//Funcs
	virtual void update() = 0;
	virtual void render() = 0;

protected:
	Game* game;
	sf::RenderWindow* window;

private:

};

