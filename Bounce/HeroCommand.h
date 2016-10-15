//
//  HeroCommand.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include "../EasySFML/Command.h"

#include "Hero.h"

class HeroCommand : public Command
{
public:
    HeroCommand(std::shared_ptr<Hero> hero, int command);
    
    void execute () override;
    void undo () override;
    
private:
    std::shared_ptr<Hero> mHero;
    int mCommand;
};
