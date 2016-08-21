//
//  Director.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/3/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Director.h"
#include "Game.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Window.h"
#include "WindowManager.h"

void Director::playGame ()
{
    while (!game()->isDone())
    {
        if (game()->isFixedFrameReady())
        {
            windowManager()->handleInput();
            game()->update();
            game()->render();
            game()->completeFixedFrame();
        }
        game()->restartClock();
    }
}

void Director::setGame (std::shared_ptr<Game> game)
{
    if (!mGame)
    {
        mGame = game;
        
        onConfigurationChange();
    }
}

void Director::setEventManager (std::shared_ptr<EventManager> manager)
{
    if (!mEventManager)
    {
        mEventManager = manager;
        
        onConfigurationChange();
    }
}

void Director::setSceneManager (std::shared_ptr<SceneManager> manager)
{
    if (!mSceneManager)
    {
        mSceneManager = manager;
        
        onConfigurationChange();
    }
}

void Director::setWindowManager (std::shared_ptr<WindowManager> manager)
{
    if (!mWindowManager)
    {
        mWindowManager = manager;
        
        onConfigurationChange();
    }
}

void Director::loadTriggers ()
{
    mEventManager->createTriggers();
    
    mGame->loadTriggers();
    mEventManager->loadTriggers();
    mSceneManager->loadTriggers();
    mWindowManager->loadTriggers();
}

void Director::onConfigurationChange ()
{
    if (mGame && mEventManager && mSceneManager && mWindowManager)
    {
        loadTriggers();
        
        std::shared_ptr<Window> mainWindow = mGame->createMainWindow();
        
        mWindowManager->addWindow(mainWindow);
    }
}