//
//  Dot.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Dot.h"
#include "Window.h"

using namespace std;

Dot::Dot (const sf::Texture * texture, const sf::Vector2f & position, const sf::Vector2u & bounds)
: mTextureSize(texture->getSize()), mPositionDelta(0.0f, 0.0f), mBounds(bounds)
{
    mDot.setTexture(*texture);
    mDot.setOrigin(mTextureSize.x / 2, mTextureSize.y / 2);
    mDot.setPosition(position);
}

Dot::~Dot ()
{
    
}

void Dot::move (const sf::Vector2f delta, float elapsedSeconds)
{
    mPositionDelta += delta;
    
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

    if ((mDot.getPosition().x + mTextureSize.x / 2 > mBounds.x &&
         mPositionDelta.x > 0) ||
        (mDot.getPosition().x - mTextureSize.x / 2 < 0 &&
         mPositionDelta.x < 0))
    {
        mPositionDelta.x = -mPositionDelta.x;
    }
    
    if ((mDot.getPosition().y + mTextureSize.y / 2 > mBounds.y &&
         mPositionDelta.y > 0) ||
        (mDot.getPosition().y - mTextureSize.y / 2 < 0 &&
         mPositionDelta.y < 0))
    {
        mPositionDelta.y = -mPositionDelta.y;
    }
    
    mDot.setPosition(mDot.getPosition() + mPositionDelta * elapsedSeconds);
}

void Dot::draw (Window * window)
{
    window->draw(mDot);
}
