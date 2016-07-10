#include "BounceGame.h"

int main()
{
    BounceGame game;

    while (!game.getWindow()->isDone())
    {
        game.handleInput();
        game.update();
        game.render();
        game.restartClock();
    }

    return EXIT_SUCCESS;
}
