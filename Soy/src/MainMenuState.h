#pragma once
#include "State.h"
#include "Gui.h"

class MainMenuState : public State
{
public:
	MainMenuState(StateStuff* stateStuff);
	virtual ~MainMenuState();

	void update();
	void render();

	void pauseState();
	void resumeState();
private:
	Gui gui;

	unsigned char selectedButton;

	std::vector<std::string>* videoModes;

	GuiItem* g;
	bool gc;
};

