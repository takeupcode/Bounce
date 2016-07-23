//
//  Dot.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Dot.h"

Dot::Dot (Window * windowPtr, const sf::Texture & texture, const sf::Vector2f position)
: mWindowPtr(windowPtr)
{
    mTextureSize = texture.getSize();

    mDot.setTexture(texture);
    mDot.setOrigin(mTextureSize.x / 2, mTextureSize.y / 2);
    mDot.setPosition(position);
    
    mPositionDelta = {0.0f, 0.0f};
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

    if ((mDot.getPosition().x + mTextureSize.x / 2 > mWindowPtr->size().x &&
         mPositionDelta.x > 0) ||
        (mDot.getPosition().x - mTextureSize.x / 2 < 0 &&
         mPositionDelta.x < 0))
    {
        mPositionDelta.x = -mPositionDelta.x;
    }
    
    if ((mDot.getPosition().y + mTextureSize.y / 2 > mWindowPtr->size().y &&
         mPositionDelta.y > 0) ||
        (mDot.getPosition().y - mTextureSize.y / 2 < 0 &&
         mPositionDelta.y < 0))
    {
        mPositionDelta.y = -mPositionDelta.y;
    }
    
    mDot.setPosition(mDot.getPosition() + mPositionDelta * elapsedSeconds);
}

void Dot::draw ()
{
    mWindowPtr->draw(mDot);
}
