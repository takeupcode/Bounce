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
: Game("Bounce", {800, 600})
{
    if (!mSphereTexture.loadFromFile(resourcePath() + "sphere.png"))
    {
        throw std::runtime_error("Could not load sphere.png.");
    }
    
    mSphereTextureSize = mSphereTexture.getSize();
    
    mDot.setTexture(mSphereTexture);
    mDot.setPosition(sf::Vector2f(400, 300));
    mDot.setOrigin(mSphereTextureSize.x / 2, mSphereTextureSize.y / 2);
    
    mPositionDelta = {0.0f, 200.0f};
}

BounceGame::~BounceGame ()
{
}

void BounceGame::handleInput ()
{
}

void BounceGame::update ()
{
    getWindow()->update();
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
    
    if ((mDot.getPosition().y + mSphereTextureSize.y / 2 > getWindow()->size().y &&
         mPositionDelta.y > 0) ||
        (mDot.getPosition().y - mSphereTextureSize.y / 2 < 0 &&
         mPositionDelta.y < 0))
    {
        mPositionDelta.y = -mPositionDelta.y;
    }
    
    mDot.setPosition(mDot.getPosition() + mPositionDelta * elapsedSeconds);
}
