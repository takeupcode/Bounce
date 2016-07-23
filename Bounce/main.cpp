#include "BounceGame.h"

int main()
{
    BounceGame game;

    while (!game.isDone())
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
