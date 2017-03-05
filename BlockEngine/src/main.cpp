
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include "ResourcePath.hpp"
#include "ResourceManager.hpp"
#include "ScreenManager.hpp"
#include "HomeScreen.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "BlockEngine");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	ResourceManager::GetInstance().LoadAll(resourcePath() + "ResourceFile.txt");
    
    ScreenManager screenManager;
    
    screenManager.AddScreen(new HomeScreen());
    
    sf::Clock clock;
    sf::Time dt;

    // Start the game loop
    while (window.isOpen())
    {
        // Calculate dt
        dt = clock.restart();
        
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
        
        // Handle input, update, and draw screens
        screenManager.HandleInput(window);
        screenManager.Update(dt.asSeconds());
        screenManager.Draw(window);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
