//
//  HeroStateSkidding.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/10/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Hero.h"
#include "HeroStateSkidding.h"

bool HeroStateSkidding::handleCommand (int command)
{
    if (HeroStateOnGround::handleCommand(command))
    {
        return true;
    }
    
    return false;
}

void HeroStateSkidding::update (float elapsedSeconds)
{
    
}
