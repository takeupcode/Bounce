#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bounce");
    
    sf::Texture sphereTexture;
    if (!sphereTexture.loadFromFile(resourcePath() + "sphere.png"))
    {
        return EXIT_FAILURE;
    }
    sf::Vector2u sphereTextureSize = sphereTexture.getSize();
    
    sf::Sprite dot(sphereTexture);
    dot.setPosition(sf::Vector2f(400, 300));
    dot.setOrigin(sphereTextureSize.x / 2, sphereTextureSize.y / 2);
    
    sf::Vector2f positionDelta(0.0f, 0.5f);

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
        
        if ((dot.getPosition().y + sphereTextureSize.x / 2 > window.getSize().y &&
            positionDelta.y > 0) ||
            (dot.getPosition().y - sphereTextureSize.x / 2 < 0 &&
             positionDelta.y < 0))
        {
            positionDelta.y = -positionDelta.y;
        }
        
        dot.setPosition(dot.getPosition() + positionDelta);

        // Clear screen
        window.clear(sf::Color::Black);
        
        window.draw(dot);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
