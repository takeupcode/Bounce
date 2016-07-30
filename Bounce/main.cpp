#include "BounceGame.h"

using namespace std;

int main()
{
    shared_ptr<BounceGame> game(new BounceGame());
    game->loadTriggers();

    while (!game->isDone())
    {
        if (game->isFixedFrameReady())
        {
            game->handleInput();
            game->update();
            game->render();
            game->completeFixedFrame();
        }
        game->restartClock();
    }

    return EXIT_SUCCESS;
}
