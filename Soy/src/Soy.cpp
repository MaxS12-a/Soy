#include "pch.h"

int main()
{
    Log::Init();

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    CORE_INFO("Window created.");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("Resources/icon.png")) {
        CORE_CRITICAL("Missing Icon.");
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    CORE_INFO("Icon loaded.");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("Resources/cute_image.jpg")) {
        CORE_CRITICAL("Mssing image!");
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    CORE_INFO("Sprite Loaded.");

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("Resources/sansation.ttf")) {
        CORE_CRITICAL("Missing font!");
        return EXIT_FAILURE;
    }

    // Lua test
    lua_State* L = luaL_newstate();
    if (luaL_dostring(L, "l = \"LUA IS WORKING\"")) { CORE_CRITICAL("LUA IS NOT FINE!"); throw("Closing application"); };
    lua_getglobal(L, "l");
    std::string luaStr = lua_tostring(L, -1);
    lua_close(L);
    CORE_INFO("LUA IS FINE!");

    sf::Text text(luaStr, font, 50);
    text.setFillColor(sf::Color::Black);
    CORE_INFO("Text created.");

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("Resources/nice_music.ogg")) {
        CORE_CRITICAL("Missing song.");
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();
    CORE_INFO("Audio is ok.");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }

    CORE_WARN("EVERYTHING IS FINE!");
    return EXIT_SUCCESS;
}
