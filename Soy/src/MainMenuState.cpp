#include "pch.h"
#include "MainMenuState.h"
#include "Game.h"
#include "MMSetingsState.h"

//Constructors
MainMenuState::MainMenuState(Game* game, sf::RenderWindow* window)
	: State(game, window), mouseClik(false), mousePressed(false)
{
    initButtons();

    mmsBgTexture.loadFromFile("Resources/Images/MMSBG.jpg");
    mmsBg.setTexture(mmsBgTexture);
    mmsBg.setPosition(0,0);

    mmsMusic.openFromFile("Resources/Sounds/MMSMusic.wav");

    mmsMusic.play();
}

MainMenuState::~MainMenuState()
{
}

//Funcs
void MainMenuState::update()
{
    updateMousePos();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (mousePressed) mouseClik = false;
        else mouseClik = true;
        mousePressed = true;
    }
    else mousePressed = false;

    //Buttons logic
    for (auto i : buttons) i.second->update(sf::Vector2i((int)mousePosView.x, (int) mousePosView.y));
    
    if (mouseClik && buttons["New Game"]->getHover()) {
        buttons["New Game"]->press();
    }
    if (mouseClik && buttons["W"]->getHover()) {
        buttons["W"]->press();
    }
    if (mouseClik && buttons["Settings"]->getHover()) {
        buttons["Settings"]->press();
        game->pushState(new MMSetingsState(game, window));
    }
    if (mouseClik && buttons["Exit"]->getHover()) {
        buttons["Exit"]->press();
        window->close();
    }
}

void MainMenuState::render()
{
    window->draw(mmsBg);

    for (auto i : buttons) i.second->render(window);
}

void MainMenuState::initButtons()
{
    buttonsFont.loadFromFile("Resources/sansation.ttf");
    
    buttonHoverSBuffer.loadFromFile("Resources/Sounds/ButtonHoverSound.ogg");
    buttonHoverS.setBuffer(buttonHoverSBuffer);

    buttonPressedSBuffer.loadFromFile("Resources/Sounds/ButtonPressedSound.ogg");
    buttonPressedS.setBuffer(buttonPressedSBuffer);

    buttonsAnchor.x = 35; buttonsAnchor.y = 275;

    buttons["New Game"] = new Button(buttonsAnchor.x, buttonsAnchor.y, 200, 75, true, sf::Color::Transparent, sf::Color::Transparent,
        "New Game", sf::Color(255, 255, 255, 255), sf::Color(255,0, 255 ,255), 50, buttonsFont, 0, sf::Color::Transparent,
        buttonHoverS, buttonPressedS);
    buttons["W"] = new Button(buttonsAnchor.x, buttonsAnchor.y + 75, 200, 75, true, sf::Color::Transparent, sf::Color::Transparent,
        "W", sf::Color(255, 255, 255, 255), sf::Color(0, 255, 0, 255), 50, buttonsFont, 0, sf::Color::Transparent,
        buttonHoverS, buttonPressedS);
    buttons["Settings"] = new Button(buttonsAnchor.x, buttonsAnchor.y + 150, 200, 75, true, sf::Color::Transparent, sf::Color::Transparent,
        "Settings", sf::Color(255, 255, 255, 255), sf::Color(0, 0, 255, 255), 50, buttonsFont, 0, sf::Color::Transparent,
        buttonHoverS, buttonPressedS);
    buttons["Exit"] = new Button(buttonsAnchor.x, buttonsAnchor.y + 225, 200, 75, true, sf::Color::Transparent, sf::Color::Transparent,
        "Exit", sf::Color(255, 255, 255, 255), sf::Color(255, 0, 0, 255), 50, buttonsFont, 0, sf::Color::Transparent,
        buttonHoverS, buttonPressedS);
}
