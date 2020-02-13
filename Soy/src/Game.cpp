#include "pch.h"
#include "Game.h"

//Constructors
Game::Game()
    : ups(0), fps(0), secondsRunning(0)
{
    window.create(sf::VideoMode::getDesktopMode(), "SFML WORKS!", sf::Style::Fullscreen);

    stateStuff = new StateStuff({ this, &window, (int)window.getSize().x, (int)window.getSize().y, 1, StateStuff::Volumes({1,1}) });

    setTargetUps(60);
    setTargetFps(60);

    //stateStack.push(new MainMenuState(stateStuff));
   
    guiScale = {1,1};

    b1 = new TextButton(0, window.getSize().y / 4 + 0, "BUTTON B1", "Resources/Fonts/spaceranger.ttf", 75,
        sf::Color::Cyan, sf::Color::Green, guiScale, Button::Left, { window.getSize().x, window.getSize().y },
        "Resources/Sounds/ButtonHoverSound.ogg", "Resources/Sounds/ButtonPressedSound.ogg");
    b2 = new TextButton(0, window.getSize().y / 4 + 100, "BUTTON B2", "Resources/Fonts/spaceranger.ttf", 75,
        sf::Color::Cyan, sf::Color::Green, guiScale, Button::Left, { window.getSize().x, window.getSize().y },
        "Resources/Sounds/ButtonHoverSound.ogg", "Resources/Sounds/ButtonPressedSound.ogg");
    b3 = new TextButton(0, window.getSize().y / 4 + 200, "BUTTON B3", "Resources/Fonts/spaceranger.ttf", 75,
        sf::Color::Cyan, sf::Color::Green, guiScale, Button::Left, { window.getSize().x, window.getSize().y },
        "Resources/Sounds/ButtonHoverSound.ogg", "Resources/Sounds/ButtonPressedSound.ogg");
    b4 = new TextButton(0, window.getSize().y / 4 + 300, "BUTTON B4", "Resources/Fonts/spaceranger.ttf", 75,
        sf::Color::Cyan, sf::Color::Green, guiScale, Button::Left, { window.getSize().x, window.getSize().y },
        "Resources/Sounds/ButtonHoverSound.ogg", "Resources/Sounds/ButtonPressedSound.ogg");

    c = 0;

    run();
}

Game::~Game()
{
    
}

//Loop Funcs
void Game::run() {
    now = std::chrono::steady_clock::now();
    upsTimer = now;
    fpsTimer = now;
    secTimer = now;
    int lfps = 0, lups = 0;

    /*Game loop*/
    while (window.isOpen()) {
        now = std::chrono::steady_clock::now();
        upsSpan = std::chrono::duration_cast<std::chrono::duration<double>>(now - upsTimer);
        fpsSpan = std::chrono::duration_cast<std::chrono::duration<double>>(now - fpsTimer);
        secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(now - secTimer);

        if (upsSpan.count() >= elapseUps) {
            update();
            lups++;
            upsTimer = now;
        }

        if (fpsSpan.count() >= elapseFps) {
            render();
            lfps++;
            fpsTimer = now;
        }

        if (secSpan.count() >= 1) {
            secondsRunning++;
            ups = lups;
            fps = lfps;
            lups = 0;
            lfps = 0;
            secTimer = now;
            LOG_TRACE("UPS/FPS: {0}/{1} | Seconds running = {2}s", ups, fps, secondsRunning);
        }
    }
}

void Game::update()
{
    //stateStack.top()->update();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        guiScale.x += 0.01; guiScale.y += 0.1;
        b1->create(window.getSize(), guiScale);
        b2->create(window.getSize(), guiScale);
        b3->create(window.getSize(), guiScale);
        b4->create(window.getSize(), guiScale);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        guiScale.x -= 0.01; guiScale.y -= 0.1;
        b1->create(window.getSize(), guiScale);
        b2->create(window.getSize(), guiScale);
        b3->create(window.getSize(), guiScale);
        b4->create(window.getSize(), guiScale);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && c== 0) {
        window.create(sf::VideoMode(1366, 768), "SFML WORKS!", sf::Style::Fullscreen);
        b1->create(window.getSize(), guiScale);
        b2->create(window.getSize(), guiScale);
        b3->create(window.getSize(), guiScale);
        b4->create(window.getSize(), guiScale);
        c++;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) mouseL = true;
    else mouseL = false;

    if(b1->update(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, mouseL)) std::cout << "b1 PRESSED" << std::endl;
    if (b2->update(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, mouseL)) std::cout << "b2 PRESSED" << std::endl;
    if (b3->update(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, mouseL)) std::cout << "b3 PRESSED" << std::endl;
    if (b4->update(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, mouseL)) std::cout << "b4 PRESSED" << std::endl;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::render()
{
    window.clear();

    window.draw(*b1);
    window.draw(*b2);
    window.draw(*b3);
    window.draw(*b4);
   // stateStack.top()->render();

    window.display();
}

//Getters and setters
const int Game::getUps() const
{
    return ups;
}

const int Game::getFps() const
{
    return fps;
}

const int Game::getTargetUps() const
{
    return targetUps;
}

void Game::setTargetUps(int targetUps)
{
    this->targetUps = targetUps;
    elapseUps = 1.f / targetUps;
}

const int Game::getTargetFps() const
{
    return targetFps;
}

void Game::setTargetFps(int targetFps)
{
    this->targetFps = targetFps;
    elapseFps = 1.f / targetFps;
}

const int Game::getSecondsRunning() const
{
    return secondsRunning;
}

//State manager
void Game::pushState(State* state)
{
    stateStack.top()->pauseState();
    stateStack.push(state);
}

void Game::popState()
{
    delete stateStack.top();
    stateStack.pop();
    stateStack.top()->resumeState();
}
