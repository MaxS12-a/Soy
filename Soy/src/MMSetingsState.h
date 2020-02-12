#pragma once
#include "State.h"
#include "Button.h"
#include "Selector.h"

class MMSetingsState :
	public State
{
public:
	//Constructors
	MMSetingsState(StateStuff* stateStuff);
	virtual ~MMSetingsState();

	//Funcs
	void update();
	void render();

	void pauseState();
	void resumeState();

	void remake();

	void initButtons();
private:
	sf::Font buttonsFont;
	sf::SoundBuffer buttonHoverSBuffer, buttonPressedSBuffer;
	sf::Sound buttonHoverS, buttonPressedS;
	std::map<std::string, Button*> buttons;
	sf::Vector2i buttonsAnchor;
	bool mouseClik, mousePressed;

	sf::Texture mmssBgTexture;
	sf::Sprite mmssBg;

	sf::Vector2i mousePosS, mousePosW;

	sf::Texture resSelectorArrowTexture;
	std::vector<sf::VideoMode> resOptions;
	Selector* resSelector;
};


