#include "pch.h"
#include "MainMenuState.h"
#include "Game.h"

MainMenuState::MainMenuState(StateStuff* stateStuff)
	:State(stateStuff)
{
	gui.addFont("Winter flakes", "Resources/Fonts/Winter flakes.ttf");

	gui.addSound("ButtonHoverSound", "Resources/Sounds/ButtonHoverSound.ogg");
	gui.addSound("ButtonPressedSound", "Resources/Sounds/ButtonPressedSound.ogg");

	gui.addGuiItem( new TextButton(1, 
		this->stateStuff->window->getSize().x/2, this->stateStuff->window->getSize().y/4,
		"BUTTON 001", gui.getFont("Winter flakes"), 75,	sf::Color::White, sf::Color::Red, 
		this->stateStuff->guiScale, GuiItem::Center, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));
	gui.addGuiItem(new TextButton(2, 
		this->stateStuff->window->getSize().x / 2, this->stateStuff->window->getSize().y / 4 + 100,
		"BUTTON 002", gui.getFont("Winter flakes"), 75,	
		sf::Color::White, sf::Color::Green, 
		this->stateStuff->guiScale, GuiItem::Center, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));
	gui.addGuiItem(new TextButton(3, 
		this->stateStuff->window->getSize().x / 2, this->stateStuff->window->getSize().y / 4 + 200,
		"BUTTON 003", gui.getFont("Winter flakes"), 75,
		sf::Color::White, sf::Color::Blue, 
		this->stateStuff->guiScale, GuiItem::Center, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));
	gui.addGuiItem(new TextButton(4, 
		this->stateStuff->window->getSize().x / 2, this->stateStuff->window->getSize().y / 4 + 300,
		"BUTTON 004", gui.getFont("Winter flakes"), 75, 
		sf::Color::White, sf::Color::Magenta, 
		this->stateStuff->guiScale, GuiItem::Center, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound"))); 
	gui.addGuiItem(new TextButton(5,
		this->stateStuff->window->getSize().x / 2, this->stateStuff->window->getSize().y / 4 + 400,
		"BUTTON 005", gui.getFont("Winter flakes"), 75,
		sf::Color::White, sf::Color::Magenta,
		this->stateStuff->guiScale, GuiItem::Center, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));

	gui.setVolume(stateStuff->volumes.guiVol);
	gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
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
