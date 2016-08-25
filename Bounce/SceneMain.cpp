//
//  SceneMain.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include <stdexcept>

#include "BounceGame.h"
#include "Director.h"
#include "EventManager.h"
#include "MoveDotCommand.h"
#include "SceneIdentities.h"
#include "SceneMain.h"
#include "SceneManager.h"
#include "Window.h"
#include "WindowIdentities.h"

#include "ResourcePath.hpp"

using namespace std;

SceneMain::SceneMain (Director * director, SceneIdentities identity, std::shared_ptr<Window> window, bool transparent, bool modal)
: Scene(director, identity, window, transparent, modal), uniformDistribution(-10.0f, 10.0f)
{
}

void SceneMain::created ()
{
    if (hasBeenCreated())
    {
        return;
    }
    Scene::created();
    
    if (!mSphereTexture.loadFromFile(resourcePath() + "sphere.png"))
    {
        throw runtime_error("Could not load sphere.png.");
    }
    
    mDot.reset(new Dot(mSphereTexture, sf::Vector2f(mWindow->size().x / 2, mWindow->size().y / 2), sf::Vector2u(mWindow->size().x, mWindow->size().y)));
    
    randomGenerator.seed(std::random_device()());
}

void SceneMain::update (float elapsedSeconds)
{
    sf::Vector2f positionDelta {0.0f, 0.0f};
    positionDelta.x += uniformDistribution(randomGenerator);
    positionDelta.y += uniformDistribution(randomGenerator);
    
    mCommands.push_back(unique_ptr<Command>(new MoveDotCommand(mDot, positionDelta, elapsedSeconds)));
    
    for (auto & cmdPtr: mCommands)
    {
        cmdPtr->execute();
    }
    mCommands.clear();
}

void SceneMain::render ()
{
    mDot->draw(mWindow.get());
}

void SceneMain::loadTriggers ()
{
    director()->eventManager()->addSubscription(EventManager::MoveCharacterLeft, "SceneMain", shared_from_this());
    director()->eventManager()->addSubscription(EventManager::MoveCharacterRight, "SceneMain", shared_from_this());
    director()->eventManager()->addSubscription(EventManager::MoveCharacterUp, "SceneMain", shared_from_this());
    director()->eventManager()->addSubscription(EventManager::MoveCharacterDown, "SceneMain", shared_from_this());
}

void SceneMain::unloadTriggers ()
{
    director()->eventManager()->removeSubscription(EventManager::MoveCharacterLeft, "SceneMain");
    director()->eventManager()->removeSubscription(EventManager::MoveCharacterRight, "SceneMain");
    director()->eventManager()->removeSubscription(EventManager::MoveCharacterUp, "SceneMain");
    director()->eventManager()->removeSubscription(EventManager::MoveCharacterDown, "SceneMain");
}

void SceneMain::notify (EventParameter eventDetails)
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
        
        float elapsedSeconds = director()->game()->elapsed().asSeconds();
        mCommands.push_back(unique_ptr<Command>(new MoveDotCommand(mDot, positionDelta, elapsedSeconds)));
    }
}
