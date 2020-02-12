#pragma once
#include "SFML/Graphics.hpp"

class Game;

struct StateStuff{
	Game* game;
	sf::RenderWindow* window;
	double guiScale;
};

class State
{
public:
	//Constructors
	State(StateStuff* stateStuff);
	virtual ~State();

	//Funcs
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void pauseState() = 0;
	virtual void resumeState() = 0;

	virtual void remake() = 0;
protected:
	StateStuff* stateStuff;
private:

};

