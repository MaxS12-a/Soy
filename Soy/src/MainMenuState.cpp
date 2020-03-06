#include "pch.h"
#include "MainMenuState.h"
#include "MMSettingsState.h"
#include "Game.h"

MainMenuState::MainMenuState(StateStuff* stateStuff)
	:State(stateStuff)
{
	// *** //

	gui.addSound("BikeChange", "Resources/Sounds/BikeChange.ogg");
	gui.addSound("Click", "Resources/Sounds/Click.ogg");
	gui.addSound("LongClick", "Resources/Sounds/LongClick.ogg");
	gui.addSound("Punun", "Resources/Sounds/Punun.ogg");
	gui.addSound("Tchum", "Resources/Sounds/Tchum.ogg");

	gui.addFont("Komikax", "Resources/Fonts/Komikax.ttf");

	// *** //

	gui.addItem(1, new SpriteButton(1920, 1080, { 1, 1 }, stateStuff->windowSize, stateStuff->guiScale,
		"Resources/Images/Gear.png", { 1.05, 1.05 }, &gui.getSound("LongClick"), &gui.getSound("BikeChange")));

	// *** //

	gui.addItem(2, new SpriteButton(1920, 0, { 1, 0 }, stateStuff->windowSize, stateStuff->guiScale,
		"Resources/Images/Sound.png", { 1.05, 1.05 }, &gui.getSound("Punun"), &gui.getSound("Tchum")));
	((SpriteButton*)gui.getItem(2))->addTexture("Resources/Images/SoundMuted.png");

	// *** //

	gui.addItem(3, new GuiSprite(1920 / 4 + 100, 0, { 0.5, 0 }, stateStuff->windowSize, stateStuff->guiScale,
		"Resources/Images/Soyura.png"));

	// *** //

	gui.addItem(4, new GuiContainer(1920 / 4 + 100, 430, stateStuff->windowSize, stateStuff->guiScale, 30));

	((GuiContainer*)gui.getItem(4))->addItem(1, new TextButton(0, 0, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"New game", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Magenta, sf::Color::Black, 10, &gui.getSound("Click"), &gui.getSound("BikeChange")));
	((GuiContainer*)gui.getItem(4))->addItem(2, new TextButton(0, 0, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Lore", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Cyan, sf::Color::Black, 10, &gui.getSound("Click"), &gui.getSound("BikeChange")));
	((GuiContainer*)gui.getItem(4))->addItem(3, new TextButton(0, 0, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Skills", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Yellow, sf::Color::Black, 10, &gui.getSound("Click"), &gui.getSound("BikeChange")));
	((GuiContainer*)gui.getItem(4))->addItem(4, new TextButton(0, 0, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Creatures", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Green, sf::Color::Black, 10, &gui.getSound("Click"), &gui.getSound("BikeChange")));
	((GuiContainer*)gui.getItem(4))->addItem(5, new TextButton(0, 0, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Exit", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Red, sf::Color::Black, 10, &gui.getSound("Click"), &gui.getSound("BikeChange")));

	gui.getItem(4)->create(stateStuff->windowSize, stateStuff->guiScale);

	// *** //

	mmMusic = new sf::Music();
	mmMusic->openFromFile("Resources/Sounds/MMSMusic.wav");
	mmMusic->setLoop(true);

	// *** //

	background = new Background(0, 0, "Resources/Images/BG.png", { 0, 0, 1920, 1080 }, 4, 60, stateStuff->windowSize);
	background->addBGMovSprite(new BGMovSprite("Resources/Images/Pixel.png", { 0, 0, 15, 15 }, 10, 16, 5, { 0, 0, 1920, 1080 }, 320, { 0, 0 }, stateStuff->windowSize));
	background->addBGMovSprite(new BGMovSprite("Resources/Images/Pixel.png", { 0, 0, 15, 15 }, 10, 8, 4, { 0, 0, 1920, 1080 }, 160, { 0, 0 }, stateStuff->windowSize));
	background->addBGMovSprite(new BGMovSprite("Resources/Images/Pixel.png", { 0, 0, 15, 15 }, 10, 4, 3, { 0, 0, 1920, 1080 }, 80, { 0, 0 }, stateStuff->windowSize));
	background->addBGMovSprite(new BGMovSprite("Resources/Images/Pixel.png", { 0, 0, 15, 15 }, 10, 2, 2, { 0, 0, 1920, 1080 }, 40, { 0, 0 }, stateStuff->windowSize));
	background->addBGMovSprite(new BGMovSprite("Resources/Images/Pixel.png", { 0, 0, 15, 15 }, 10, 1, 1, { 0, 0, 1920, 1080 }, 10, { 5, 0 }, stateStuff->windowSize));

	// *** //

	mmMusic->setVolume(stateStuff->volumes.musicVol);
	gui.setVolume(stateStuff->volumes.guiVol);

	mmMusic->play();
}

MainMenuState::~MainMenuState()
{
	delete mmMusic;
	delete background;
}

void MainMenuState::update()
{
	updateMouse();

	background->update();

	selectedObject = gui.update(mouseState);

	switch (selectedObject)
	{
	case 1:
		stateStuff->game->pushState(new MMSettingsState(stateStuff, mmMusic));
		break;
	case 2:
		if (((SpriteButton*)gui.getItem(2))->getActualTexture() == 0) {
			((SpriteButton*)gui.getItem(2))->setTexture(1);
			stateStuff->volumes.mute();
			gui.setVolume(stateStuff->volumes.guiVol);
			mmMusic->setVolume(stateStuff->volumes.musicVol);
		}
		else if (((SpriteButton*)gui.getItem(2))->getActualTexture() == 1) {
			((SpriteButton*)gui.getItem(2))->setTexture(0);
			stateStuff->volumes.mute();
			gui.setVolume(stateStuff->volumes.guiVol);
			mmMusic->setVolume(stateStuff->volumes.musicVol);
		}
		break;
	case 4:
		int* a = (int*)((GuiContainer*)gui.getItem(4))->getInfo();
		int s = *a;
		delete a;

		switch (s)
		{
		case 1:
			std::cout << "1" << std::endl;
			break;
		case 2:
			std::cout << "2" << std::endl;
			break;
		case 3:
			std::cout << "3" << std::endl;
			break;
		case 4:
			std::cout << "4" << std::endl;
			break;
		case 5:
			std::cout << "5" << std::endl;
			stateStuff->window->close();
			break;
		}
		break;
	}
}

void MainMenuState::render()
{
	background->render(stateStuff->window);
	gui.render(stateStuff->window);
}

void MainMenuState::pauseState()
{
}

void MainMenuState::resumeState()
{
}
