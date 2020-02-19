#include "pch.h"
#include "MMSettingsState.h"
#include "Game.h"

MMSettingsState::MMSettingsState(StateStuff* stateStuff, sf::Music* mmMusic)
	:State(stateStuff), mmMusic(mmMusic)
{
	gui.addSound("BikeChange", "Resources/Sounds/BikeChange.ogg");
	gui.addSound("Click", "Resources/Sounds/Click.ogg");
	gui.addSound("LongClick", "Resources/Sounds/LongClick.ogg");
	gui.addSound("Punun", "Resources/Sounds/Punun.ogg");
	gui.addSound("Tchum", "Resources/Sounds/Tchum.ogg");

	gui.addFont("Komikax", "Resources/Fonts/Komikax.ttf");

	gui.addItem(1, new GuiSprite(960, 540, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale, "Resources/Images/AlphaGear.png"));


	gui.addItem(2, new GuiContainer(250, 200, stateStuff->windowSize, stateStuff->guiScale, 20));

	((GuiContainer*)gui.getItem(2))->addItem(1, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Resolution", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Magenta, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(2, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Gui scale", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Cyan, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(3, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Fullscreen", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Yellow, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(4, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Volume", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Green, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(5, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Apply", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Red, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(6, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Apply & return", gui.getFont("Komikax"), 85, sf::Color(127, 127, 127, 255), sf::Color(60, 60, 60, 255), sf::Color::Black, 10, &gui.getSound("Click"), nullptr));

	gui.getItem(2)->create(stateStuff->windowSize, stateStuff->guiScale);

	gui.addItem(3, new GuiContainer(1920-250, 200, stateStuff->windowSize, stateStuff->guiScale, 20));

	std::vector<std::string>* options = new std::vector<std::string>();
	auto modes = sf::VideoMode::getFullscreenModes();
	for (int i = 0; i < modes.size(); i++)
		options->push_back(std::string(std::to_string(modes[i].width) + "x" + std::to_string(modes[i].height)));

	((GuiContainer*)gui.getItem(3))->addItem(1, new Selector(0, 0, { 1, 0.5 }, stateStuff->windowSize, stateStuff->guiScale, 20, options,
		0, gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Yellow, sf::Color::Black, 10, &gui.getSound("Click"), nullptr,
		"Resources/Images/Arrow.png", {1.05,1.05}, &gui.getSound("Punun"), &gui.getSound("Tchum")));
	
	std::vector<std::string>* options2 = new std::vector<std::string>();
	for (int i = 1; i <= 40; i++)
		options2->push_back(std::string(std::to_string(i/(double)10)));

	((GuiContainer*)gui.getItem(3))->addItem(2, new Selector(0, 0, { 1, 0.5 }, stateStuff->windowSize, stateStuff->guiScale, 20, options2,
		0, gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Yellow, sf::Color::Black, 10, &gui.getSound("Click"), nullptr,
		"Resources/Images/Arrow.png", { 1.05, 1.05 }, &gui.getSound("Punun"), &gui.getSound("Tchum")));

	((GuiContainer*)gui.getItem(3))->addItem(3, new TextButton(0, 0, { 1, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Fullscreen", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Yellow, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(3))->addItem(4, new TextButton(0, 0, { 1, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Volume", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Green, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(3))->addItem(5, new TextButton(0, 0, { 1, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Apply", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Red, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));

	gui.getItem(3)->create(stateStuff->windowSize, stateStuff->guiScale);

	background = new Background(0, 0, "Resources/Images/MMSSBG.jpg", { 0, 0, 1920, 1080 }, 1, -1, stateStuff->windowSize);
	background->addBGMovSprite(new BGMovSprite("Resources/Images/WPixel.png", { 0, 0, 15, 15 }, 10, 20, 6, { 0, 0, 1920, 900 }, 380, { 0, -0.2 }, stateStuff->windowSize));

	mmMusic->setVolume(stateStuff->volumes.musicVol);
	gui.setVolume(stateStuff->volumes.guiVol);
}

MMSettingsState::~MMSettingsState()
{
	delete background;
}

void MMSettingsState::update()
{
	updateMouse();

	background->update();

	selectedObject = gui.update(mouseState);

	switch (selectedObject)
	{

	case 2:
		int* a = (int*)((GuiContainer*)gui.getItem(2))->getInfo();
		int s = *a;
		delete a;

		switch (s)
		{
		case 1:
			
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			stateStuff->game->popState();
			break;
		}
		break;
	}
}

void MMSettingsState::render()
{
	background->render(stateStuff->window);
	gui.render(stateStuff->window);
}

void MMSettingsState::pauseState()
{
}

void MMSettingsState::resumeState()
{
}
