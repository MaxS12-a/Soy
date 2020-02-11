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

	virtual void updateMousePos();
protected:
	Game* game;
	sf::RenderWindow* window;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
private:

};

