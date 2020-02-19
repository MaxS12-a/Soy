#pragma once
#include "State.h"
#include "Gui.h" 
#include "Background.h"

class MMSettingsState :
	public State
{
public:
	MMSettingsState(StateStuff* stateStuff, sf::Music* mmMusic);
	virtual ~MMSettingsState();

	void update();
	void render();

	void pauseState();
	void resumeState();
private:
	Gui gui;
	Background* background;
	int selectedObject;

	sf::Music* mmMusic;
};

