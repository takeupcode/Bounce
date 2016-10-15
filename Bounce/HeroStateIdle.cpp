//
//  HeroStateIdle.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/10/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Hero.h"
#include "HeroStateIdle.h"

bool HeroStateIdle::handleCommand (int command)
{
    if (HeroStateOnGround::handleCommand(command))
    {
        return true;
    }
    
    switch (command)
    {
        case Hero::CommandWalkEast:
            hero()->mVelocity.x += 7.0f;
            hero()->setNewState(&Hero::mStateWalking);
            break;
            
        case Hero::CommandWalkWest:
            hero()->mVelocity.x -= 7.0f;
            hero()->setNewState(&Hero::mStateWalking);
            break;
            
        case Hero::CommandJump:
            hero()->mVelocity.y -= 150.0f;
            hero()->setNewState(&Hero::mStateJumping);
            break;
    }
    
    return false;
}

void HeroStateIdle::update (float elapsedSeconds)
{
    HeroStateOnGround::update(elapsedSeconds);
}

void HeroStateIdle::enter ()
{
    if (hero()->mDirection == Direction::East)
    {
        hero()->mAnimation->setAnimation(Hero::IdleEast);
    }
    else if (hero()->mDirection == Direction::West)
    {
        hero()->mAnimation->setAnimation(Hero::IdleWest);
    }
    hero()->setSize(hero()->mAnimation->size());
}
