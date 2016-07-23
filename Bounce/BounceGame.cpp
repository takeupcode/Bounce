//
//  BounceGame.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include <stdexcept>

#include "BounceGame.h"

#include "ResourcePath.hpp"

BounceGame::BounceGame ()
: Game("Bounce", {800, 600}), randomX(0.0f), randomY(0.0f), uniformDistribution(-10.0f, 10.0f)
{
    if (!mSphereTexture.loadFromFile(resourcePath() + "sphere.png"))
    {
        throw std::runtime_error("Could not load sphere.png.");
    }
    
    mSphereTextureSize = mSphereTexture.getSize();
    
    mDot.setTexture(mSphereTexture);
    mDot.setPosition(sf::Vector2f(400, 300));
    mDot.setOrigin(mSphereTextureSize.x / 2, mSphereTextureSize.y / 2);
    
    mPositionDelta = {0.0f, 0.0f};
    
    randomGenerator.seed(std::random_device()());
}

BounceGame::~BounceGame ()
{
}

void BounceGame::handleInput ()
{
    getWindow()->handleInput();
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        mPositionDelta.x -= 10.0f;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        mPositionDelta.x += 10.0f;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        mPositionDelta.y -= 10.0f;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        mPositionDelta.y += 10.0f;
    }
    
    randomX = uniformDistribution(randomGenerator);
    randomY = uniformDistribution(randomGenerator);
    
    mPositionDelta.x += randomX;
    mPositionDelta.y += randomY;
    
    if (mPositionDelta.x > 500.0f)
    {
        mPositionDelta.x = 500.0f;
    }
    else if (mPositionDelta.x < -500.0f)
    {
        mPositionDelta.x = -500.0f;
    }
    
    if (mPositionDelta.y > 500.0f)
    {
        mPositionDelta.y = 500.0f;
    }
    else if (mPositionDelta.y < -500.0f)
    {
        mPositionDelta.y = -500.0f;
    }
}

void BounceGame::update ()
{
    moveDot();
}

void BounceGame::render ()
{
    getWindow()->drawBegin();
    getWindow()->draw(mDot);
    getWindow()->drawEnd();
}

void BounceGame::moveDot ()
{
    float elapsedSeconds = elapsed().asSeconds();
    
    if ((mDot.getPosition().x + mSphereTextureSize.x / 2 > getWindow()->size().x &&
         mPositionDelta.x > 0) ||
        (mDot.getPosition().x - mSphereTextureSize.x / 2 < 0 &&
         mPositionDelta.x < 0))
    {
        mPositionDelta.x = -mPositionDelta.x;
    }
    
    if ((mDot.getPosition().y + mSphereTextureSize.y / 2 > getWindow()->size().y &&
         mPositionDelta.y > 0) ||
        (mDot.getPosition().y - mSphereTextureSize.y / 2 < 0 &&
         mPositionDelta.y < 0))
    {
        mPositionDelta.y = -mPositionDelta.y;
    }
    
    mDot.setPosition(mDot.getPosition() + mPositionDelta * elapsedSeconds);
}
