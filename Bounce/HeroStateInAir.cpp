//
//  HeroStateInAir.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/10/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Hero.h"
#include "HeroStateInAir.h"

bool HeroStateInAir::handleCommand (int command)
{
    return false;
}

void HeroStateInAir::update (float elapsedSeconds)
{
    hero()->mVelocity.x += hero()->mAcceleration.x;
    hero()->mVelocity.y += hero()->mAcceleration.y;
    
    SpriteAnimation * surface = hero()->mSurfaceTile;
    if (surface != nullptr)
    {
        // Make sure that collisions can happen each update by ensuring
        // this object tries to drop at least one pixel each frame.
        hero()->mPosition.y += 1;
        
        if (hero()->mVelocity.x == 0)
        {
            hero()->setNewState(&Hero::mStateIdle);
        }
        else if (hero()->mVelocity.x > -200.0f && hero()->mVelocity.x < 200.0f)
        {
            hero()->setNewState(&Hero::mStateWalking);
        }
        else
        {
            hero()->setNewState(&Hero::mStateRunning);
        }
        return;
    }
    
    hero()->mPosition.x += hero()->mVelocity.x * elapsedSeconds;
    hero()->mPosition.y += hero()->mVelocity.y * elapsedSeconds;
    
    if (hero()->mPosition.x + hero()->mAnimation->scaledSize().x / 2 > hero()->mBounds.x)
    {
        hero()->mPosition.x = hero()->mBounds.x - hero()->mAnimation->scaledSize().x / 2;
        hero()->mVelocity.x = 0;
    }
    else if (hero()->mPosition.x - hero()->mAnimation->scaledSize().x / 2 < 0)
    {
        hero()->mPosition.x = hero()->mAnimation->scaledSize().x / 2;
        hero()->mVelocity.x = 0;
    }
    
    if (hero()->mPosition.y > hero()->mBounds.y)
    {
        hero()->mPosition.y = hero()->mBounds.y;
        hero()->mVelocity.y = 0;
    }
    else if (hero()->mPosition.y - hero()->mAnimation->scaledSize().y < 0 )
    {
        hero()->mPosition.y = hero()->mAnimation->scaledSize().y;
    }
}
