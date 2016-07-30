//
//  BounceGame.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include <stdexcept>

#include "BounceGame.h"
#include "MoveDotCommand.h"

#include "ResourcePath.hpp"

BounceGame::BounceGame ()
: Game("Bounce", {800, 600}), uniformDistribution(-10.0f, 10.0f)
{
    if (!mSphereTexture.loadFromFile(resourcePath() + "sphere.png"))
    {
        throw std::runtime_error("Could not load sphere.png.");
    }
    
    mDotPtr = new Dot(getWindow(), mSphereTexture, sf::Vector2f(400, 300));
    
    randomGenerator.seed(std::random_device()());
}

BounceGame::~BounceGame ()
{
    delete mDotPtr;
}

void BounceGame::loadTriggers()
{
    getWindow()->getEventManager()->addSubscription(EventManager::MoveCharacterLeft, "BounceGame", shared_from_this());
    getWindow()->getEventManager()->addSubscription(EventManager::MoveCharacterRight, "BounceGame", shared_from_this());
    getWindow()->getEventManager()->addSubscription(EventManager::MoveCharacterUp, "BounceGame", shared_from_this());
    getWindow()->getEventManager()->addSubscription(EventManager::MoveCharacterDown, "BounceGame", shared_from_this());
}

void BounceGame::notify (Trigger::EventParameter eventDetails)
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
    mCommands.push_back(new MoveDotCommand(mDotPtr, positionDelta, elapsedSeconds));
}

void BounceGame::update ()
{
    sf::Vector2f positionDelta {0.0f, 0.0f};
    positionDelta.x += uniformDistribution(randomGenerator);
    positionDelta.y += uniformDistribution(randomGenerator);
    
    float elapsedSeconds = elapsed().asSeconds();
    mCommands.push_back(new MoveDotCommand(mDotPtr, positionDelta, elapsedSeconds));

    for (Command * cmdPtr: mCommands)
    {
        cmdPtr->execute();
        delete cmdPtr;
    }
    mCommands.clear();
}

void BounceGame::render ()
{
    getWindow()->drawBegin();
    mDotPtr->draw();
    getWindow()->drawEnd();
}
