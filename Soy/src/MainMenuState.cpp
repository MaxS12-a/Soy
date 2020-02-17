#include "pch.h"
#include "MainMenuState.h"
#include "Game.h"

MainMenuState::MainMenuState(StateStuff* stateStuff)
	:State(stateStuff)
{
	gui.addFont("Winter flakes", "Resources/Fonts/Winter flakes.ttf");

	gui.addSound("ButtonHoverSound", "Resources/Sounds/ButtonHoverSound.ogg");
	gui.addSound("ButtonPressedSound", "Resources/Sounds/ButtonPressedSound.ogg");

	gui.addGuiItem(1, new GuiSprite(this->stateStuff->windowSize.x / 2, 100, "Resources/Images/Sveknider.png", this->stateStuff->guiScale,
		{0.5, 0.5}, this->stateStuff->windowSize));

	videoModes = new std::vector<std::string>();
	auto modes = sf::VideoMode::getFullscreenModes();
	for (int i = 0; i < modes.size(); i++)
		videoModes->push_back(std::string(std::to_string(modes[i].width) + "x" + std::to_string(modes[i].height)));

	gui.addGuiItem(2, new GuiContainer(1920/2, 300,
		this->stateStuff->guiScale, this->stateStuff->window->getSize(), 15));

	((GuiContainer*)gui.getItem(2))->addItem(1, new TextButton(	0, 0,
		"BUTTON 001", gui.getFont("Winter flakes"), 75, sf::Color::White, sf::Color::Red,
		this->stateStuff->guiScale, { 0.5 , 0.5 }, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));
	((GuiContainer*)gui.getItem(2))->addItem(2, new TextButton(	0, 0,
		"BUTTON 002", gui.getFont("Winter flakes"), 75,
		sf::Color::White, sf::Color::Green,
		this->stateStuff->guiScale, { 0.5 , 0.5 }, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));
	((GuiContainer*)gui.getItem(2))->addItem(3, new TextButton(	0, 0,
		"BUTTON 003", gui.getFont("Winter flakes"), 75,
		sf::Color::White, sf::Color::Blue,
		this->stateStuff->guiScale, { 0.5 , 0.5 }, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));
	((GuiContainer*)gui.getItem(2))->addItem(4, new TextButton(	0, 0,
		"BUTTON 004", gui.getFont("Winter flakes"), 75,
		sf::Color::White, sf::Color::Magenta,
		this->stateStuff->guiScale, { 0.5 , 0.5 }, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));
	((GuiContainer*)gui.getItem(2))->addItem(5, new TextButton(	0, 0,
		"BUTTON 005", gui.getFont("Winter flakes"), 75,
		sf::Color::White, sf::Color::Magenta,
		this->stateStuff->guiScale, { 0.5 , 0.5 }, this->stateStuff->window->getSize(), false,
		gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound")));

	gui.getItem(2)->create(this->stateStuff->windowSize, this->stateStuff->guiScale);

	gui.setVolume(stateStuff->volumes.guiVol);

	gc = false;
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update()
{
	updateMouse();

	if (selectedButton = gui.update(mouseState)) std::cout << "Gui ID pressed: " << (int)selectedButton << std::endl;

	if (selectedButton == 2) {
		int* a = (int*)gui.getItem(2)->getInfo();
		
		if (*a == 1) {
			if (!g) {
				g = ((GuiContainer*)gui.getItem(2))->getItem(1);
				((GuiContainer*)gui.getItem(2))->addItem(1, new Selector(0, 0,
					this->stateStuff->guiScale, this->stateStuff->windowSize, gui.getFont("Winter flakes"),
					75, sf::Color::White, sf::Color::Yellow,
					true, "Resources/Images/Button-Blank-Red-icon.png", "Resources/Images/Button-Blank-Gray-icon.png", { 1.15, 1.15 },
					gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound"),
					gui.getSound("ButtonHoverSound"), gui.getSound("ButtonPressedSound"),
					225, videoModes, 0));
				gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
			}
			else if(!gc){
				std::string* aux = (std::string*)((GuiContainer*)gui.getItem(2))->getItem(1)->getInfo();
				std::istringstream f(*aux);
				delete aux;
				std::string s1, s2;
				std::getline(f, s1, 'x');
				std::getline(f, s2, '\0');
				stateStuff->window->create(sf::VideoMode(std::stoi(s1), std::stoi(s2)), "SF", sf::Style::Close | sf::Style::Titlebar);
				stateStuff->windowSize = stateStuff->window->getSize();
				
				GuiItem* a = ((GuiContainer*)gui.getItem(2))->getItem(1);
				((GuiContainer*)gui.getItem(2))->addItem(1, g);
				g = a;

				gc = true;

				gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
			}
			else {
				GuiItem* a = ((GuiContainer*)gui.getItem(2))->getItem(1);
				((GuiContainer*)gui.getItem(2))->addItem(1, g);
				g = a;
				gc = false;
				gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
			}
		}	
		else if (*a == 2) {
			stateStuff->guiScale.x -= 0.25;
			stateStuff->guiScale.y -= 0.25;
			gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
		}
		else if (*a == 3) {
			stateStuff->window->create(sf::VideoMode(1366,768), "SF", sf::Style::Fullscreen);
			stateStuff->windowSize = stateStuff->window->getSize();
			gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
		}
		else if (*a == 4) {
			stateStuff->window->create(sf::VideoMode(800,600), "SF", sf::Style::Fullscreen);
			stateStuff->windowSize = stateStuff->window->getSize();
			gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
		}
		else if (*a == 5) {
			stateStuff->window->create(sf::VideoMode(1920, 1080), "SF", sf::Style::Fullscreen);
			stateStuff->windowSize = stateStuff->window->getSize();
			gui.create(this->stateStuff->windowSize, this->stateStuff->guiScale);
		}
		delete a;
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
