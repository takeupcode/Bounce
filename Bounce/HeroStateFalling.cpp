//
//  HeroStateFalling.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/10/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Hero.h"
#include "HeroStateFalling.h"

bool HeroStateFalling::handleCommand (int command)
{
    if (HeroStateInAir::handleCommand(command))
    {
        return true;
    }
    
    return false;
}

void HeroStateFalling::update (float elapsedSeconds)
{
    if (hero()->mVelocity.y > 400.0f)
    {
        hero()->mVelocity.y = 400.0f;
    }
    
    HeroStateInAir::update(elapsedSeconds);
}

void HeroStateFalling::enter ()
{
    if (hero()->mDirection == Direction::East)
    {
        hero()->mAnimation->setAnimation(Hero::FallStartEast);
    }
    else if (hero()->mDirection == Direction::West)
    {
        hero()->mAnimation->setAnimation(Hero::FallStartWest);
    }
    hero()->setSize(hero()->mAnimation->size());
}
