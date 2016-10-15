//
//  HeroStateMaster.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/9/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include "../EasySFML/EntityState.h"

class Hero;

class HeroStateMaster : public EntityState
{
public:
    Hero * hero ()
    {
        return mHero;
    }
    
private:
    friend class Hero;
    
    void setHero (Hero * hero)
    {
        mHero = hero;
    }
    
    Hero * mHero;
};
