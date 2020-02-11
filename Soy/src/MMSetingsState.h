#pragma once
#include "State.h"
#include "Button.h"

class MMSetingsState :
	public State
{
public:
	//Constructors
	MMSetingsState(Game* game, sf::RenderWindow* window);
	virtual ~MMSetingsState();

	//Funcs
	void update();
	void render();

	void initButtons();
private:
	sf::Font buttonsFont;
	sf::SoundBuffer buttonHoverSBuffer, buttonPressedSBuffer;
	sf::Sound buttonHoverS, buttonPressedS;
	std::map<std::string, Button*> buttons;
	sf::Vector2i buttonsAnchor;
	bool mouseClik, mousePressed;

	sf::Vector2i mousePos, mousePosWindow;

	sf::Music mmsMusic;
	sf::Texture mmsBgTexture;
	sf::Sprite mmsBg;
};

