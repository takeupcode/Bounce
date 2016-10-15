//
//  HeroStateWalking.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/10/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Hero.h"
#include "HeroStateWalking.h"

bool HeroStateWalking::handleCommand (int command)
{
    if (HeroStateOnGround::handleCommand(command))
    {
        return true;
    }
    
    switch (command)
    {
        case Hero::CommandWalkEast:
            hero()->mVelocity.x += 7.0f;
            if (hero()->mDirection == Direction::West &&
                hero()->mVelocity.x > 0)
            {
                hero()->mAnimation->setAnimation(Hero::WalkEast);
                hero()->mDirection = Direction::East;
            }
            break;

        case Hero::CommandWalkWest:
            hero()->mVelocity.x -= 7.0f;
            if (hero()->mDirection == Direction::East &&
                hero()->mVelocity.x < 0)
            {
                hero()->mAnimation->setAnimation(Hero::WalkWest);
                hero()->mDirection = Direction::West;
            }
            break;
            
        case Hero::CommandJump:
            hero()->mVelocity.y -= 150.0f;
            hero()->setNewState(&Hero::mStateJumping);
            break;
    }
    
    return false;
}

void HeroStateWalking::update (float elapsedSeconds)
{
    if (hero()->mVelocity.x > 200.0f)
    {
        hero()->mVelocity.x = 200.0f;
    }
    else if (hero()->mVelocity.x < -200.0f)
    {
        hero()->mVelocity.x = -200.0f;
    }
    
    HeroStateOnGround::update(elapsedSeconds);
}

void HeroStateWalking::enter ()
{
    if (hero()->mVelocity.x > 0)
    {
        hero()->mAnimation->setAnimation(Hero::WalkEast);
        hero()->mDirection = Direction::East;
    }
    else if (hero()->mVelocity.x < 0)
    {
        hero()->mAnimation->setAnimation(Hero::WalkWest);
        hero()->mDirection = Direction::West;
    }
    hero()->setSize(hero()->mAnimation->size());
}
