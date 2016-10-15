//
//  HeroStateOnGround.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/10/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Hero.h"
#include "HeroStateOnGround.h"

bool HeroStateOnGround::handleCommand (int command)
{
    return false;
}

void HeroStateOnGround::update (float elapsedSeconds)
{
    hero()->mVelocity.x += hero()->mAcceleration.x;
    hero()->mVelocity.y += hero()->mAcceleration.y;
    
    SpriteAnimation * surface = hero()->mSurfaceTile;
    if (surface == nullptr)
    {
        hero()->setNewState(&Hero::mStateFalling);
        return;
    }

    if (hero()->mVelocity.x == 0)
    {
        hero()->setNewState(&Hero::mStateIdle);
    }
    else
    {
        float friction = 0.0f;
        FrameTag * tag = surface->tag("friction");
        if (tag && tag->type() == FrameTag::TagType::FloatTag)
        {
            friction = tag->floatValue();
            if (hero()->mVelocity.x > 0)
            {
                hero()->mVelocity.x += friction;
                if (hero()->mVelocity.x < 0)
                {
                    hero()->mVelocity.x = 0;
                    hero()->setNewState(&Hero::mStateIdle);
                }
            }
            else if (hero()->mVelocity.x < 0)
            {
                hero()->mVelocity.x -= friction;
                if (hero()->mVelocity.x > 0)
                {
                    hero()->mVelocity.x = 0;
                    hero()->setNewState(&Hero::mStateIdle);
                }
            }
        }
    }

    hero()->mPosition.x += hero()->mVelocity.x * elapsedSeconds;
    
    // Make sure that collisions can happen each update by ensuring
    // this object tries to drop at least one pixel each frame.
    hero()->mPosition.y += 1;
    
    if (hero()->mPosition.x + hero()->mAnimation->scaledSize().x / 2 > hero()->mBounds.x)
    {
        hero()->mPosition.x = hero()->mBounds.x - hero()->mAnimation->scaledSize().x / 2;
        hero()->mVelocity.x = 0;
        hero()->setNewState(&Hero::mStateIdle);
    }
    else if (hero()->mPosition.x - hero()->mAnimation->scaledSize().x / 2 < 0)
    {
        hero()->mPosition.x = hero()->mAnimation->scaledSize().x / 2;
        hero()->mVelocity.x = 0;
        hero()->setNewState(&Hero::mStateIdle);
    }
}
