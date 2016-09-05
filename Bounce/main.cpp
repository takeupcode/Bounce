#include "../EasySFML/Director.h"
#include "../EasySFML/EventManager.h"
#include "../EasySFML/SceneManager.h"
#include "../EasySFML/TextureManager.h"
#include "../EasySFML/WindowManager.h"

#include "BounceGame.h"

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
