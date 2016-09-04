#include "BounceGame.h"
#include "Director.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "WindowManager.h"

using namespace std;

int main()
{
    Director director;
    director.setGame(shared_ptr<Game>(new BounceGame(&director)));
    director.setEventManager(shared_ptr<EventManager>(new EventManager(&director)));
    director.setSceneManager(shared_ptr<SceneManager>(new SceneManager(&director)));
    director.setTextureManager(shared_ptr<TextureManager>(new TextureManager(&director)));
    director.setWindowManager(shared_ptr<WindowManager>(new WindowManager(&director)));
    
    director.playGame();

    return EXIT_SUCCESS;
}
