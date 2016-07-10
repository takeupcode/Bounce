#include "BounceGame.h"

int main()
{
    BounceGame game;

    while (!game.getWindow()->isDone())
    {
        game.handleInput();
        game.update();
        game.render();
    }

    return EXIT_SUCCESS;
}
