#pragma once
#include "State.h"

class MainMenuState : public State
{
public:
	//Constructors
	MainMenuState(Game* game, sf::RenderWindow* window);
	virtual ~MainMenuState();

	//Funcs
	void update();
	void render();
private:
	sf::Image icon;
	sf::Texture texture;
	sf::Font font;
	sf::Sprite sprite;
	sf::Music music;
	sf::Text text;
	std::string luaStr;
};

