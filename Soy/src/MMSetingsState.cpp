#include "pch.h"
#include "MMSetingsState.h"
#include "Game.h"

//Constructors
MMSetingsState::MMSetingsState(StateStuff* stateStuff)
    : State(stateStuff), mouseClik(false), mousePressed(false)
{
    mmssBgTexture.loadFromFile("Resources/Images/MMSSBG.jpg");
    mmssBg.setTexture(mmssBgTexture);
    mmssBg.setPosition(0, 0);

    resSelectorArrowTexture.loadFromFile("Resources/Images/Arrow.png");
    resOptions = sf::VideoMode::getFullscreenModes();

    remake();
}

MMSetingsState::~MMSetingsState()
{
    for (auto i : buttons) delete i.second;
    delete resSelector;
}

//Funcs
void MMSetingsState::update()
{
    mousePosS = sf::Mouse::getPosition();
    mousePosW = sf::Mouse::getPosition(*stateStuff->window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (mousePressed) mouseClik = false;
        else mouseClik = true;
        mousePressed = true;
    }
    else { mousePressed = false; mouseClik = false; }

    //Buttons logic
    for (auto i : buttons) i.second->update(sf::Vector2i((int)mousePosW.x, (int)mousePosW.y));

    if (mouseClik && buttons["Resolution"]->getHover()) {
        buttons["Resolution"]->press();
        stateStuff->window->create(sf::VideoMode(1366,768), "?", sf::Style::Fullscreen); 
        remake();
    }
    if (mouseClik && buttons["GuiSize"]->getHover()) {
        buttons["GuiSize"]->press();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { stateStuff->guiScale += 0.1; remake();}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { stateStuff->guiScale -= 0.1; remake();}
    }
    if (mouseClik && buttons["Vol"]->getHover()) {
        buttons["Vol"]->press();
    }
    if (mouseClik && buttons["Return"]->getHover()) {
        buttons["Return"]->press();
        stateStuff->game->popState();
    }
}

void MMSetingsState::render()
{
    stateStuff->window->draw(mmssBg);
    
    for (auto i : buttons) i.second->render(stateStuff->window);
    
    resSelector->render(stateStuff->window);
}

void MMSetingsState::pauseState()
{
}

void MMSetingsState::resumeState()
{
}

void MMSetingsState::remake()
{
    initButtons();
    mmssBg.setScale(stateStuff->window->getSize().x / (float)mmssBgTexture.getSize().x,
        stateStuff->window->getSize().y / (float)mmssBgTexture.getSize().y);
}

void MMSetingsState::initButtons()
{
    for (auto i : buttons) delete i.second;
    if(resSelector) delete resSelector;

    if (!buttons["Resolution"]) {
        buttonsFont.loadFromFile("Resources/sansation.ttf");

        buttonHoverSBuffer.loadFromFile("Resources/Sounds/ButtonHoverSound.ogg");
        buttonHoverS.setBuffer(buttonHoverSBuffer);

        buttonPressedSBuffer.loadFromFile("Resources/Sounds/ButtonPressedSound.ogg");
        buttonPressedS.setBuffer(buttonPressedSBuffer);
    }

    buttonsAnchor.x = stateStuff->window->getSize().x * 0.5; buttonsAnchor.y = stateStuff->window->getSize().y * 0.3;
    
    buttons["Resolution"] = new Button(buttonsAnchor.x, buttonsAnchor.y,
        "Resolution", sf::Color(0, 0, 0, 255), sf::Color(255, 0, 255, 255), 80 * stateStuff->guiScale, buttonsFont,
        buttonHoverS, buttonPressedS);

    buttons["GuiSize"] = new Button(buttonsAnchor.x, buttonsAnchor.y + 100 * stateStuff->guiScale,
        "GuiSize", sf::Color(0, 0, 0, 255), sf::Color(0, 255, 0, 255), 80 * stateStuff->guiScale, buttonsFont,
        buttonHoverS, buttonPressedS);
    buttons["Vol"] = new Button(buttonsAnchor.x, buttonsAnchor.y + 200 * stateStuff->guiScale,
        "Vol", sf::Color(0, 0, 0, 255), sf::Color(0, 0, 255, 255), 80 * stateStuff->guiScale, buttonsFont,
        buttonHoverS, buttonPressedS);
    buttons["Return"] = new Button(buttonsAnchor.x, buttonsAnchor.y + 300 * stateStuff->guiScale,
        "Return", sf::Color(0, 0, 0, 255), sf::Color(255, 0, 0, 255), 80 * stateStuff->guiScale, buttonsFont,
        buttonHoverS, buttonPressedS);

    resSelector = new Selector(buttons["Resolution"]->getGlobalBounds().left + buttons["Resolution"]->getGlobalBounds().width,
        buttons["Resolution"]->getGlobalBounds().top, 80 * stateStuff->guiScale, buttonsFont, sf::Color(0, 0, 0, 255), sf::Color(255, 0, 255, 255),
        resSelectorArrowTexture, &resOptions, buttonHoverS, buttonPressedS, stateStuff->guiScale);
}

