#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "BounceGame.h"

int main(int, char const**)
{
    BounceGame game;

    // Start the game loop
    while (!game.getWindow()->isDone())
    {
        game.handleInput();
        game.update();
        game.render();
    }

    return EXIT_SUCCESS;
}
