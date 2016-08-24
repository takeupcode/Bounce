//
//  BounceGame.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include <stdexcept>

#include "BounceGame.h"
#include "Director.h"
#include "SceneIdentities.h"
#include "SceneMain.h"
#include "SceneMainMenu.h"
#include "SceneManager.h"
#include "SceneSplash.h"
#include "Window.h"
#include "WindowIdentities.h"
#include "WindowManager.h"

using namespace std;

BounceGame::BounceGame (Director * director)
: Game(director)
{
}

BounceGame::~BounceGame ()
{
}

void BounceGame::registerScenes ()
{
    director()->sceneManager()->registerScene<SceneSplash>(SceneIdentities::Splash, director()->windowManager()->mainWindow(), false, false);
    director()->sceneManager()->registerScene<SceneMain>(SceneIdentities::Level01, director()->windowManager()->mainWindow(), false, false);
    director()->sceneManager()->registerScene<SceneMainMenu>(SceneIdentities::MainMenu, director()->windowManager()->mainWindow(), false, true);
}

void BounceGame::setInitialScenes ()
{
    director()->sceneManager()->activateScene(SceneIdentities::Splash);
}

shared_ptr<Window> BounceGame::createMainWindow () const
{
    shared_ptr<Window> mainWindow(new Window(director(), mainWindowIdentity(), "Bounce", {MainWindowWidth, MainWindowHeight}));
    
    return mainWindow;
}

int BounceGame::mainWindowIdentity () const
{
    return static_cast<int>(WindowIdentities::MainWindow);
}
