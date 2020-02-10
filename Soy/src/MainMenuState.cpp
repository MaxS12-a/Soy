#include "pch.h"
#include "MainMenuState.h"
#include "Game.h"

//Constructors
MainMenuState::MainMenuState(Game* game, sf::RenderWindow* window)
	: State(game, window)
{
    // Set the Icon
    if (!icon.loadFromFile("Resources/icon.png")) LOG_CRITICAL("Missing Icon.");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    LOG_INFO("Icon loaded.");
    
    // Load a sprite to display
    if (!texture.loadFromFile("Resources/cute_image.jpg")) LOG_CRITICAL("Mssing image!");
    sprite.setTexture(texture);
    LOG_INFO("Sprite created.");
    
    // Create a graphical text to display
    if (!font.loadFromFile("Resources/sansation.ttf")) LOG_CRITICAL("Missing font!");
    
    // Lua test
    lua_State* L = luaL_newstate();
    if (luaL_dostring(L, "l = \"LUA IS WORKING\"")) { LOG_CRITICAL("LUA IS NOT FINE!"); throw("Closing application"); };
    lua_getglobal(L, "l");
    luaStr = lua_tostring(L, -1);
    lua_close(L);
    LOG_INFO("LUA IS FINE!");
    
    text.setString(luaStr);
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Black);
    LOG_INFO("Text created.");
    
    // Load a music to play
    if (!music.openFromFile("Resources/nice_music.ogg")) LOG_CRITICAL("Missing song.");
    
    music.play();
    music.setLoop(true);
    music.setPitch(1.3);
    LOG_INFO("Audio is ok.");
}

MainMenuState::~MainMenuState()
{
}


//Funcs
void MainMenuState::update()
{
    if (game->getSecondsRunning() % 4 == 0) text.move(1,1);
}

void MainMenuState::render()
{
    window->draw(sprite);
    window->draw(text);
}
