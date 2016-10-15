//
//  HeroStateWalking.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/10/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include "HeroStateOnGround.h"

class HeroStateWalking : public HeroStateOnGround
{
public:
    bool handleCommand (int command) override;
    
    void update (float elapsedSeconds) override;
    
    void enter () override;
};
