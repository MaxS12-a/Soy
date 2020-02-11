#pragma once
#include "MainMenuState.h"

class Game
{
public:
	//Constructors
	Game();
	virtual ~Game();

	//Loop Funcs
	void run();
	void update();
	void render();

	//Getters and setters
	const int getUps() const;
	const int getFps() const;
	const int getTargetUps() const;
	void setTargetUps(int targetUps);
	const int getTargetFps() const;
	void setTargetFps(int targetFps);
	const int getSecondsRunning() const;

	//State manager
	void pushState(State* state);
	void popState();

private:
	sf::RenderWindow window;
	sf::Event event;
	sf::View windowView;

	State* mms;
	std::stack<State*> stateStack;

	//Game loop variables
	int ups, fps, targetUps, targetFps, secondsRunning;
	double elapseUps, elapseFps;
	std::chrono::steady_clock::time_point now, upsTimer, fpsTimer, secTimer;
	std::chrono::duration<double> upsSpan, fpsSpan, secSpan;
};

