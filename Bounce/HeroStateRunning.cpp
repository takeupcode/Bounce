//
//  HeroStateRunning.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/10/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Hero.h"
#include "HeroStateRunning.h"

bool HeroStateRunning::handleCommand (int command)
{
    if (HeroStateOnGround::handleCommand(command))
    {
        return true;
    }
    
    return false;
}

void HeroStateRunning::update (float elapsedSeconds)
{
    if (hero()->mVelocity.x > 400.0f)
    {
        hero()->mVelocity.x = 400.0f;
    }
    else if (hero()->mVelocity.x < -400.0f)
    {
        hero()->mVelocity.x = -400.0f;
    }
    
    HeroStateOnGround::update(elapsedSeconds);
}

void HeroStateRunning::enter ()
{
    if (hero()->mVelocity.x > 0)
    {
        hero()->mAnimation->setAnimation(Hero::RunEast);
        hero()->mDirection = Direction::East;
    }
    else if (hero()->mVelocity.x < 0)
    {
        hero()->mAnimation->setAnimation(Hero::RunWest);
        hero()->mDirection = Direction::West;
    }
    hero()->setSize(hero()->mAnimation->size());
}
