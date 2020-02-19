#pragma once
class Game;

struct StateStuff{
	Game* game;
	sf::RenderWindow* window;
	sf::Vector2u windowSize;
	sf::Vector2f guiScale;
	
	struct Volumes {
		Volumes(bool muted,	float musicVol,	float guiVol);

		bool muted;
		float musicVol;
		float guiVol;
	
		void mute();
		void increaseMusicVol(float vol);
		void increaseGuiVol(float vol);

	private:
		float musicVolUM;
		float guiVolUM;

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

