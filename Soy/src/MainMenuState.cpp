#include "pch.h"
#include "MainMenuState.h"
#include "Game.h"

MainMenuState::MainMenuState(StateStuff* stateStuff)
	:State(stateStuff)
{
	gui.addFont("Winter flakes", "Resources/Fonts/Winter flakes.ttf");

	gui.addSound("ButtonHoverSound", "Resources/Sounds/ButtonHoverSound.ogg");
	gui.addSound("ButtonPressedSound", "Resources/Sounds/ButtonPressedSound.ogg");

	gui.addGuiItem(1, new TextButton(
		this->stateStuff->window->getSize().x/2, this->stateStuff->window->getSize().y/4,
		"BUTTON 001", gui.getFont("Winter flakes"), 75,	sf::Color::White, sf::Color::Red, 
		this->stateStuff->guiScale, {0.5 , 0.5}, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));
	
	gui.addGuiItem(2, new TextButton(
		this->stateStuff->window->getSize().x / 2, this->stateStuff->window->getSize().y / 4 + 100,
		"BUTTON 002", gui.getFont("Winter flakes"), 75,	
		sf::Color::White, sf::Color::Green,
		this->stateStuff->guiScale, { 0.5 , 0.5 }, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));
	
	gui.addGuiItem(3, new TextButton( 
		this->stateStuff->window->getSize().x / 2, this->stateStuff->window->getSize().y / 4 + 200,
		"BUTTON 003", gui.getFont("Winter flakes"), 75,
		sf::Color::White, sf::Color::Blue, 
		this->stateStuff->guiScale, { 0.5 , 0.5 }, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));
	
	gui.addGuiItem(4, new TextButton(
		this->stateStuff->window->getSize().x / 2, this->stateStuff->window->getSize().y / 4 + 300,
		"BUTTON 004", gui.getFont("Winter flakes"), 75, 
		sf::Color::White, sf::Color::Magenta, 
		this->stateStuff->guiScale, { 0.5 , 0.5 }, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound"))); 
	
	gui.addGuiItem(5, new TextButton(
		this->stateStuff->window->getSize().x / 2, this->stateStuff->window->getSize().y / 4 + 400,
		"BUTTON 005", gui.getFont("Winter flakes"), 75,
		sf::Color::White, sf::Color::Magenta,
		this->stateStuff->guiScale, { 0.5 , 0.5 }, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));

	gui.addGuiItem(6, new SpriteButton(	0, 0,
		"Resources/Images/Button-Blank-Gray-icon.png", "", this->stateStuff->guiScale, { 0 , 0 },
		this->stateStuff->windowSize, gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound"), {1.2, 1.2}));
	
	gui.addGuiItem(7, new SpriteButton( 0, this->stateStuff->windowSize.y, 
		"Resources/Images/Button-Blank-Blue-icon.png", "", this->stateStuff->guiScale, {0 , 1 },
		this->stateStuff->windowSize, gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound"), { 1.2, 1.2 }));

	gui.addGuiItem(8, new SpriteButton( this->stateStuff->windowSize.x, 0,
		"Resources/Images/Button-Blank-Green-icon.png", "", this->stateStuff->guiScale, { 1 , 0 },
		this->stateStuff->windowSize, gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound"), { 1.2, 1.2 }));

	gui.addGuiItem(9, new SpriteButton( this->stateStuff->windowSize.x, this->stateStuff->windowSize.y,
		"Resources/Images/Button-Blank-Yellow-icon.png", "", this->stateStuff->guiScale, { 1 , 1 },
		this->stateStuff->windowSize, gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound"), { 1.2, 1.2 }));

	videoModes = new std::vector<std::string>();
	auto modes = sf::VideoMode::getFullscreenModes();
	for (int i = 0; i < modes.size(); i++)
		videoModes->push_back(std::string(std::to_string(modes[i].width) + "x" + std::to_string(modes[i].height)));

	gui.addGuiItem(10, new Selector(
		this->stateStuff->window->getSize().x / 2, this->stateStuff->window->getSize().y / 4 + 400,
		this->stateStuff->guiScale, {0.5, 0.5}, this->stateStuff->windowSize, gui.getFont("Winter flakes"),
		75, sf::Color::White, sf::Color::Yellow, 
		true, "Resources/Images/Button-Blank-Red-icon.png", "Resources/Images/Button-Blank-Gray-icon.png", {1.15, 1.15},
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound"),
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound"),
		200, videoModes, 0));

	gui.setVolume(stateStuff->volumes.guiVol);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update()
{
	updateMouse();

	selectedButton = gui.update(mouseState);
	if (selectedButton) std::cout << "Gui ID pressed: " << (int)selectedButton << std::endl;

	if (selectedButton == 1) {
		stateStuff->guiScale.x += 0.25;
		stateStuff->guiScale.y += 0.25;
		gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
	}
	if (selectedButton == 2) {
		stateStuff->guiScale.x -= 0.25;
		stateStuff->guiScale.y -= 0.25;
		gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
	}
	if (selectedButton == 3) {
		stateStuff->window->create(sf::VideoMode(1366,768), "SF", sf::Style::Fullscreen);
		stateStuff->windowSize = stateStuff->window->getSize();
		gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
	}
	if (selectedButton == 4) {
		stateStuff->window->create(sf::VideoMode(800,600), "SF", sf::Style::Fullscreen);
		stateStuff->windowSize = stateStuff->window->getSize();
		gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
	}
	if (selectedButton == 5) {
		stateStuff->window->create(sf::VideoMode(1920, 1080), "SF", sf::Style::Fullscreen);
		stateStuff->windowSize = stateStuff->window->getSize();
		gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
	}
	if (selectedButton == 6) {
		stateStuff->window->create(sf::VideoMode::getDesktopMode(), "SF", sf::Style::None);
		stateStuff->windowSize = stateStuff->window->getSize();
		gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
	}
	if (selectedButton == 7) {
		stateStuff->window->create(sf::VideoMode(1920, 1080), "SF", sf::Style::Close | sf::Style::Titlebar);
		stateStuff->windowSize = stateStuff->window->getSize();
		gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
	}
	if (selectedButton == 8) {
		stateStuff->window->create(sf::VideoMode(1366, 768), "SF", sf::Style::Close | sf::Style::Titlebar);
		stateStuff->windowSize = stateStuff->window->getSize();
		gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
	}
	if (selectedButton == 9) {
		stateStuff->window->create(sf::VideoMode(1000, 1000), "SF", sf::Style::Close | sf::Style::Titlebar);
		stateStuff->windowSize = stateStuff->window->getSize();
		gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
	}
	if (selectedButton == 10) {
		std::cout << "!!:" <<  *((std::string*)gui.getItem(10)->getInfo()) << std::endl;
	}
}

void MainMenuState::render()
{
	gui.render(stateStuff->window);
}

void MainMenuState::pauseState()
{
}

void MainMenuState::resumeState()
{
}
