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
#include "EventManager.h"
#include "MoveDotCommand.h"
#include "Window.h"
#include "WindowManager.h"

#include "ResourcePath.hpp"

using namespace std;

BounceGame::BounceGame (Director * director)
: GameShared(director), uniformDistribution(-10.0f, 10.0f)
{
    if (!mSphereTexture.loadFromFile(resourcePath() + "sphere.png"))
    {
        throw runtime_error("Could not load sphere.png.");
    }
    
    mDot.reset(new Dot(mSphereTexture, sf::Vector2f(MainWindowWidth / 2, MainWindowHeight / 2), sf::Vector2u(MainWindowWidth, MainWindowHeight)));
    
    randomGenerator.seed(std::random_device()());
}

BounceGame::~BounceGame ()
{
}

void BounceGame::update ()
{
    sf::Vector2f positionDelta {0.0f, 0.0f};
    positionDelta.x += uniformDistribution(randomGenerator);
    positionDelta.y += uniformDistribution(randomGenerator);
    
    float elapsedSeconds = elapsed().asSeconds();
    mCommands.push_back(unique_ptr<Command>(new MoveDotCommand(mDot, positionDelta, elapsedSeconds)));
    
    for (auto & cmdPtr: mCommands)
    {
        cmdPtr->execute();
    }
    mCommands.clear();
}

void BounceGame::render ()
{
    if (!mMainWindow)
    {
        mMainWindow = director()->windowManager()->mainWindow();
    }
    mMainWindow->drawBegin();
    mDot->draw(mMainWindow.get());
    mMainWindow->drawEnd();
}

void BounceGame::loadDerivedTriggers()
{
    director()->eventManager()->addSubscription(EventManager::MoveCharacterLeft, "BounceGame", shared_from_base());
    director()->eventManager()->addSubscription(EventManager::MoveCharacterRight, "BounceGame", shared_from_base());
    director()->eventManager()->addSubscription(EventManager::MoveCharacterUp, "BounceGame", shared_from_base());
    director()->eventManager()->addSubscription(EventManager::MoveCharacterDown, "BounceGame", shared_from_base());
}

void BounceGame::notify (EventParameter eventDetails)
{
    if (eventDetails.name() == EventManager::MoveCharacterLeft ||
        eventDetails.name() == EventManager::MoveCharacterRight ||
        eventDetails.name() == EventManager::MoveCharacterUp ||
        eventDetails.name() == EventManager::MoveCharacterDown)
    {
        sf::Vector2f positionDelta {0.0f, 0.0f};
        
        if (eventDetails.name() == EventManager::MoveCharacterLeft)
        {
            positionDelta.x -= 10.0f;
        }
        else if (eventDetails.name() == EventManager::MoveCharacterRight)
        {
            positionDelta.x += 10.0f;
        }
        else if (eventDetails.name() == EventManager::MoveCharacterUp)
        {
            positionDelta.y -= 10.0f;
        }
        else if (eventDetails.name() == EventManager::MoveCharacterDown)
        {
            positionDelta.y += 10.0f;
        }
        
        float elapsedSeconds = elapsed().asSeconds();
        mCommands.push_back(unique_ptr<Command>(new MoveDotCommand(mDot, positionDelta, elapsedSeconds)));
    }
    else
    {
        Game::notify(eventDetails);
    }
}

shared_ptr<Window> BounceGame::createMainWindow () const
{
    shared_ptr<Window> mainWindow(new Window(director(), mainWindowIdentity(), "Bounce", {MainWindowWidth, MainWindowHeight}));
    
    return mainWindow;
}

int BounceGame::mainWindowIdentity () const
{
    return 1;
}
