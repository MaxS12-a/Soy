#pragma once
#include "State.h"
#include "Button.h"

class MainMenuState : public State
{
public:
	//Constructors
	MainMenuState(StateStuff* stateStuff);
	virtual ~MainMenuState();

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

	sf::Music mmsMusic;
	sf::Texture mmsBgTexture;
	sf::Sprite mmsBg;

	sf::Vector2i mousePosS, mousePosW;
};

