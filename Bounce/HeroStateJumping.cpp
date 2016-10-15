//
//  HeroStateJumping.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/10/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Hero.h"
#include "HeroStateJumping.h"

bool HeroStateJumping::handleCommand (int command)
{
    if (HeroStateInAir::handleCommand(command))
    {
        return true;
    }
    
    return false;
}

void HeroStateJumping::update (float elapsedSeconds)
{
    if (hero()->mVelocity.y < -400.0f)
    {
        hero()->mVelocity.y = -400.0f;
    }
    
    HeroStateInAir::update(elapsedSeconds);
}

void HeroStateJumping::enter ()
{
    if (hero()->mDirection == Direction::East)
    {
        hero()->mAnimation->setAnimation(Hero::JumpStartEast);
    }
    else if (hero()->mDirection == Direction::West)
    {
        hero()->mAnimation->setAnimation(Hero::JumpStartWest);
    }
    hero()->setSize(hero()->mAnimation->size());
}
