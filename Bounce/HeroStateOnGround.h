//
//  HeroStateOnGround.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 10/9/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include "HeroStateMaster.h"

class HeroStateOnGround : public HeroStateMaster
{
public:
    bool handleCommand (int command) override;
    
    void update (float elapsedSeconds) override;
};
