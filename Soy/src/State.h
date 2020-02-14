#pragma once
#include "SFML/Graphics.hpp"

class Game;

struct StateStuff{
	Game* game;
	sf::RenderWindow* window;
	sf::Vector2u windowSize;
	sf::Vector2f guiScale;
	
	struct Volumes {
		Volumes(float musicVol, float guiVol) : musicVol(musicVol), guiVol(guiVol) {};
		float musicVol;
		float guiVol;
	
		void increaseMusicVol(float vol) {
			musicVol += vol;
			if (musicVol >= 100) musicVol = 100;
			else if (musicVol <= 0) musicVol = 0;
		}

		void increaseGuiVol(float vol) {
			guiVol += vol;
			if (guiVol >= 100) guiVol = 100;
			else if (guiVol <= 0) guiVol = 0;
		}

	} volumes;
};

struct MouseState {
	sf::Vector2i mousePosScreen, mousePosWindow;
	bool mouseClickLeft, mousePressedLeft, mouseReleasedLeft;
	bool mouseClickRight, mousePressedRight, mouseReleasedRight;
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

	virtual void updateMouse();
protected:
	StateStuff* stateStuff;

	MouseState mouseState;
private:

};

