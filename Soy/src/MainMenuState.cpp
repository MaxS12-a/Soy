#include "pch.h"
#include "MainMenuState.h"
#include "Game.h"

MainMenuState::MainMenuState(StateStuff* stateStuff)
	:State(stateStuff)
{
	gui.addSound("BikeChange", "Resources/Sounds/BikeChange.ogg");
	gui.addSound("Click", "Resources/Sounds/Click.ogg");
	gui.addSound("LongClick", "Resources/Sounds/LongClick.ogg");

	gui.addFont("spaceranger", "Resources/Fonts/spaceranger.ttf");

	gui.addItem(1, new SpriteButton(0, 1080, {0, 1}, stateStuff->windowSize, stateStuff->guiScale,
		"Resources/Images/Gear.png", {1.04, 1.04}, gui.getSound("LongClick"), gui.getSound("BikeChange")));

	gui.addItem(2, new GuiSprite(1920 / 2, 0, { 0.5, 0 }, stateStuff->windowSize, stateStuff->guiScale,
		"Resources/Images/Kalamaharu.png"));

	gui.addItem(3, new GuiContainer(1920 / 2, 400, stateStuff->windowSize, stateStuff->guiScale, 15));

	((GuiContainer*)gui.getItem(3))->addItem(1, new TextButton(0, 0, { 0.5, 0.5}, stateStuff->windowSize, stateStuff->guiScale,
		"New game", gui.getFont("spaceranger"), 65, sf::Color::White, sf::Color::Magenta, true, gui.getSound("Click"), gui.getSound("BikeChange")));
	((GuiContainer*)gui.getItem(3))->addItem(2, new TextButton(0, 0, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Lore", gui.getFont("spaceranger"), 65, sf::Color::White, sf::Color::Cyan, false, gui.getSound("Click"), gui.getSound("BikeChange")));
	((GuiContainer*)gui.getItem(3))->addItem(3, new TextButton(0, 0, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Skills", gui.getFont("spaceranger"), 65, sf::Color::White, sf::Color::Yellow, false, gui.getSound("Click"), gui.getSound("BikeChange")));
	((GuiContainer*)gui.getItem(3))->addItem(4, new TextButton(0, 0, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Creatures", gui.getFont("spaceranger"), 65, sf::Color::White, sf::Color::Green, false, gui.getSound("Click"), gui.getSound("BikeChange")));
	((GuiContainer*)gui.getItem(3))->addItem(5, new TextButton(0, 0, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Exit", gui.getFont("spaceranger"), 65, sf::Color::White, sf::Color::Red, false, gui.getSound("Click"), gui.getSound("BikeChange")));

	gui.getItem(3)->create(stateStuff->windowSize, stateStuff->guiScale);

	mmMusic = new sf::Music();
	mmMusic->openFromFile("Resources/Sounds/MMSMusic.wav");
	mmMusic->setVolume(stateStuff->volumes.musicVol);
	mmMusic->setLoop(true);
	mmMusic->play();

	bgmovsprite = new BGMovSprite("Resources/Images/Pixel.png", { 0, 0, 11, 11 }, 10, 15, 10, { 0, 0, 10, 1080 }, 1950, {1, 0}, stateStuff->windowSize);
}

MainMenuState::~MainMenuState()
{
	delete mmMusic;
}

void MainMenuState::update()
{
	updateMouse();

	bgmovsprite->update();

	selectedObject = gui.update(mouseState);


}

void MainMenuState::render()
{
	bgmovsprite->render(stateStuff->window);
	gui.render(stateStuff->window);
}

void MainMenuState::pauseState()
{
}

void MainMenuState::resumeState()
{
}
