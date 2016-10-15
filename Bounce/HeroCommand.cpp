//
//  HeroCommand.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "HeroCommand.h"

HeroCommand::HeroCommand(std::shared_ptr<Hero> hero, int command)
: mHero(hero), mCommand(command)
{ }

void HeroCommand::execute ()
{
    mHero->handleCommand(mCommand);
}

void HeroCommand::undo ()
{
    // This command does not support undo because there are too many
    // outside factors such as time that would affect the outcome.
}
