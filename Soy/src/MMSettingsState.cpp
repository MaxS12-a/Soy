#include "pch.h"
#include "MMSettingsState.h"
#include "Game.h"

MMSettingsState::MMSettingsState(StateStuff* stateStuff, sf::Music* mmMusic)
	:State(stateStuff), mmMusic(mmMusic)
{
	// *** //

	gui.addSound("BikeChange", "Resources/Sounds/BikeChange.ogg");
	gui.addSound("Click", "Resources/Sounds/Click.ogg");
	gui.addSound("LongClick", "Resources/Sounds/LongClick.ogg");
	gui.addSound("Punun", "Resources/Sounds/Punun.ogg");
	gui.addSound("Tchum", "Resources/Sounds/Tchum.ogg");

	gui.addFont("Komikax", "Resources/Fonts/Komikax.ttf");

	// *** //

	gui.addItem(1, new GuiSprite(960, 540, { 0.5, 0.5 }, stateStuff->windowSize, stateStuff->guiScale, "Resources/Images/AlphaGear.png"));

	// *** //

	gui.addItem(2, new GuiContainer(250, 200, stateStuff->windowSize, stateStuff->guiScale, 15));

	((GuiContainer*)gui.getItem(2))->addItem(1, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Resolution", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Magenta, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(2, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Gui scale", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Cyan, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(3, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Fullscreen", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Yellow, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(4, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Antialiasing", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Green, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(5, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Volume", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Green, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(6, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Apply", gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Red, sf::Color::Black, 10, &gui.getSound("Click"), nullptr));
	((GuiContainer*)gui.getItem(2))->addItem(7, new TextButton(0, 0, { 0, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Apply & return", gui.getFont("Komikax"), 85, sf::Color(127, 127, 127, 255), sf::Color(60, 60, 60, 255), sf::Color::Black, 10, &gui.getSound("Click"), nullptr));

	gui.getItem(2)->create(stateStuff->windowSize, stateStuff->guiScale);

	// *** //

	gui.addItem(3, new GuiContainer(1770, 200, stateStuff->windowSize, stateStuff->guiScale, 15));

	std::vector<std::string>* options = new std::vector<std::string>();
	auto modes = sf::VideoMode::getFullscreenModes();
	for (int i = 0; i < modes.size(); i++)
		options->push_back(std::string(std::to_string(modes[i].width) + "x" + std::to_string(modes[i].height)));

	((GuiContainer*)gui.getItem(3))->addItem(1, new Selector(0, 0, { 1, 0.5 }, stateStuff->windowSize, stateStuff->guiScale, 20, options,
		0, gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Yellow, sf::Color::Black, 10, &gui.getSound("Click"), nullptr,
		"Resources/Images/Arrow.png", {1.05,1.05}, &gui.getSound("Punun"), &gui.getSound("Tchum")));
	
	std::vector<std::string>* options2 = new std::vector<std::string>();
	for (int i = 1; i <= 10; i++) {
		std::string aux(std::to_string((double)(i * 0.25)));
		
		std::istringstream f(aux);
		std::getline(f, aux, '0');

		if (aux[0] == '.') aux = '0' + aux;
		else if (aux[aux.size() - 2] == '.') aux += '0';

		options2->push_back(aux);
	}

	((GuiContainer*)gui.getItem(3))->addItem(2, new Selector(0, 0, { 1, 0.5 }, stateStuff->windowSize, stateStuff->guiScale, 20, options2,
		0, gui.getFont("Komikax"), 85, sf::Color::White, sf::Color::Yellow, sf::Color::Black, 10, &gui.getSound("Click"), nullptr,
		"Resources/Images/Arrow.png", { 1.05, 1.05 }, &gui.getSound("Punun"), &gui.getSound("Tchum")));

	((GuiContainer*)gui.getItem(3))->addItem(3, new GuiCheckBox(-100, 0, {1, 0.5}, stateStuff->windowSize, stateStuff->guiScale,
		"Resources/Images/Checkbox.png", { 0, 0, 100, 100 }, {1, 1.1}, &gui.getSound("Punun"), &gui.getSound("Click")));

	((GuiContainer*)gui.getItem(3))->addItem(4, new GuiCheckBox(-100, 0, { 1, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Resources/Images/Checkbox.png", { 0, 0, 100, 100 }, { 1, 1.1 }, &gui.getSound("Punun"), &gui.getSound("Click")));

	std::vector<std::string>* options3 = new std::vector<std::string>();
	for (int i = 0; i <= 100; i++)
		options3->push_back(std::string(std::to_string(i)));

	((GuiContainer*)gui.getItem(3))->addItem(5, new GuiSlider(0, 0, { 1, 0.5 }, stateStuff->windowSize, stateStuff->guiScale,
		"Resources/Images/SliderBar.png", "Resources/Images/SliderBarFilled.png", "Resources/Images/SliderItem.png", sf::Color(0,0,255,220),
		options3, 16, gui.getFont("Komikax"), 30, sf::Color(255, 215, 0, 255), sf::Color::Black, 6, &gui.getSound("Click"), nullptr));

	gui.getItem(3)->create(stateStuff->windowSize, stateStuff->guiScale);

	// *** //

	background= new Background(0, 0, "Resources/Images/MMSSBG.jpg", { 0, 0, 1920, 1080 }, 1, -1, stateStuff->windowSize);
	background->addBGMovSprite(new BGMovSprite("Resources/Images/WPixel.png", { 0, 0, 15, 15 }, 10, 20, 6, { 0, 0, 1920, 900 }, 380, { 0, -0.2 }, stateStuff->windowSize));

	// *** //

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
		case 5: // APPLY
			applyChanges(false);
			break;
		case 6: // APPLY AND RETURN
			applyChanges(true);
			stateStuff->game->popState();
			break;
		}
		break;
	}
}

void MMSettingsState::applyChanges(bool ret)
{
	// Geting new Res
	std::string* aux = (std::string*)((GuiContainer*)gui.getItem(3))->getItem(1)->getInfo();
	std::istringstream f(*aux);
	delete aux;
	std::string s1, s2;
	std::getline(f, s1, 'x');
	std::getline(f, s2, '\0');
	sf::Vector2u newRes = { (unsigned)std::stoi(s1), (unsigned)std::stoi(s2) };
	
	// Getting new GUI Scale
	aux = (std::string*)((GuiContainer*)gui.getItem(3))->getItem(2)->getInfo();
	double newGuiScale = std::stod(*aux);
	delete aux;

	// Getting fullscreen
	bool* aux2 = (bool*)((GuiContainer*)gui.getItem(3))->getItem(3)->getInfo();
	bool fullScreen = *aux2;
	delete aux2;

	// Getting antialiasing
	aux2 = (bool*)((GuiContainer*)gui.getItem(3))->getItem(4)->getInfo();
	bool antialiasing = *aux2;
	delete aux2;

	// Getting volume
	aux = (std::string*)((GuiContainer*)gui.getItem(3))->getItem(2)->getInfo();
	int newVolume = std::stoi(*aux);
	delete aux;

	std::cout << "New res: " << newRes.x << " " << newRes.y << std::endl;
	std::cout << "New guiScale: " << newGuiScale << std::endl;
	std::cout << "New fullScreen: " << fullScreen << std::endl;
	std::cout << "New antialiasing: " << antialiasing << std::endl;
	std::cout << "New volume: " << newVolume << std::endl;
}

void MMSettingsState::render()
{
	background->render(stateStuff->window);
	gui.render(stateStuff->window);

	/*sf::RectangleShape a;
	a.setFillColor(sf::Color(100,100,100,100));
	sf::FloatRect ab = ((GuiContainer*)gui.getItem(3))->getItem(3)->getGlobalBounds();
	a.setPosition(ab.left, ab.top);
	a.setSize(sf::Vector2f(ab.width, ab.height));
	stateStuff->window->draw(a);*/
}

void MMSettingsState::pauseState()
{
}

void MMSettingsState::resumeState()
{
}
