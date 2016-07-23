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
: Game("Bounce", {800, 600}), randomX(0.0f), randomY(0.0f), uniformDistribution(-10.0f, 10.0f)
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

void BounceGame::handleInput ()
{
    getWindow()->handleInput();
    
    sf::Vector2f positionDelta {0.0f, 0.0f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        positionDelta.x -= 10.0f;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        positionDelta.x += 10.0f;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        positionDelta.y -= 10.0f;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        positionDelta.y += 10.0f;
    }
    
    randomX = uniformDistribution(randomGenerator);
    randomY = uniformDistribution(randomGenerator);
    
    positionDelta.x += randomX;
    positionDelta.y += randomY;
    
    float elapsedSeconds = elapsed().asSeconds();
    mCommands.push_back(new MoveDotCommand(mDotPtr, positionDelta, elapsedSeconds));
}

void BounceGame::update ()
{
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
