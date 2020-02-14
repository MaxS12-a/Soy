#include "pch.h"
#include "Game.h"

//Constructors
Game::Game()
    : ups(0), fps(0), secondsRunning(0)
{
    window.create(sf::VideoMode::getDesktopMode(), "SFML WORKS!", sf::Style::Fullscreen);

    stateStuff = new StateStuff({ this, &window, window.getSize(), { 1,1 }, StateStuff::Volumes(50,50)});
    stateStack.push(new MainMenuState(stateStuff));

    setTargetUps(60);
    setTargetFps(60);

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
    stateStack.top()->update();

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::render()
{
     window.clear();
    
     stateStack.top()->render();
    
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
