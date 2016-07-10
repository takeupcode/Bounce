#include "BounceGame.h"

int main()
{
    BounceGame game;

    while (!game.getWindow()->isDone())
    {
        if (game.isFixedFrameReady())
        {
            game.handleInput();
            game.update();
            game.render();
            game.completeFixedFrame();
        }
        game.restartClock();
    }

    return EXIT_SUCCESS;
}
