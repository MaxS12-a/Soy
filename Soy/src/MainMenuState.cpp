#include "pch.h"
#include "MainMenuState.h"
#include "Game.h"
#include "MMSetingsState.h"

//Constructors
MainMenuState::MainMenuState(StateStuff* stateStuff)
	: State(stateStuff), mouseClik(false), mousePressed(false)
{
    mmsBgTexture.loadFromFile("Resources/Images/MMSBG.jpg");
    mmsBg.setTexture(mmsBgTexture);
    mmsBg.setPosition(0,0);
    
    remake();

    mmsMusic.openFromFile("Resources/Sounds/MMSMusic.wav");

    mmsMusic.play();

}

MainMenuState::~MainMenuState()
{
    for (auto i : buttons) delete i.second;
}

//Funcs
void MainMenuState::update()
{
    mousePosS = sf::Mouse::getPosition();
    mousePosW = sf::Mouse::getPosition(*stateStuff->window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (mousePressed) mouseClik = false;
        else mouseClik = true;
        mousePressed = true;
    }
    else {mousePressed = false; mouseClik = false;}

    //Buttons logic
    for (auto i : buttons) i.second->update(sf::Vector2i((int)mousePosW.x, (int) mousePosW.y));
    
    if (mouseClik && buttons["New Game"]->getHover()) {
        buttons["New Game"]->press();
    }
    if (mouseClik && buttons["W"]->getHover()) {
        buttons["W"]->press();
    }
    if (mouseClik && buttons["Settings"]->getHover()) {
        buttons["Settings"]->press();
        stateStuff->game->pushState(new MMSetingsState(stateStuff));
    }
    if (mouseClik && buttons["Exit"]->getHover()) {
        buttons["Exit"]->press();
        stateStuff->window->close();
    }
}

void MainMenuState::render()
{
    stateStuff->window->draw(mmsBg);

    for (auto i : buttons) i.second->render(stateStuff->window);
}

void MainMenuState::pauseState()
{        
    mmsMusic.pause();
}

void MainMenuState::resumeState()
{
    mmsMusic.play();
    remake();
}

void MainMenuState::remake()
{
    initButtons();
    mmsBg.setScale(stateStuff->window->getSize().x / (float)mmsBg.getGlobalBounds().width,
        stateStuff->window->getSize().y / (float)mmsBg.getGlobalBounds().height);
}


void MainMenuState::initButtons()
{
    for (auto i : buttons) delete i.second;

    if (!buttons["New Game"]) {
        buttonsFont.loadFromFile("Resources/sansation.ttf");

        buttonHoverSBuffer.loadFromFile("Resources/Sounds/ButtonHoverSound.ogg");
        buttonHoverS.setBuffer(buttonHoverSBuffer);

        buttonPressedSBuffer.loadFromFile("Resources/Sounds/ButtonPressedSound.ogg");
        buttonPressedS.setBuffer(buttonPressedSBuffer);  
    }

    buttonsAnchor.x = stateStuff->window->getSize().x * 0.5; buttonsAnchor.y = stateStuff->window->getSize().y * 0.3;

    buttons["New Game"] = new Button(buttonsAnchor.x, buttonsAnchor.y,
        "New Game", sf::Color(255, 255, 255, 255), sf::Color(255,0, 255 ,255), 80 * stateStuff->guiScale, buttonsFont,
        buttonHoverS, buttonPressedS);
    buttons["W"] = new Button(buttonsAnchor.x, buttonsAnchor.y + 100 * stateStuff->guiScale,
        "W", sf::Color(255, 255, 255, 255), sf::Color(0, 255, 0, 255), 80 * stateStuff->guiScale, buttonsFont,
        buttonHoverS, buttonPressedS);
    buttons["Settings"] = new Button(buttonsAnchor.x, buttonsAnchor.y + 200 * stateStuff->guiScale,
        "Settings", sf::Color(255, 255, 255, 255), sf::Color(0, 0, 255, 255), 80 * stateStuff->guiScale, buttonsFont,
        buttonHoverS, buttonPressedS);
    buttons["Exit"] = new Button(buttonsAnchor.x, buttonsAnchor.y + 300 * stateStuff->guiScale,
        "Exit", sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 255), 80 * stateStuff->guiScale, buttonsFont,
        buttonHoverS, buttonPressedS);
}
