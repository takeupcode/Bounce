//
//  MoveHeroCommand.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "MoveHeroCommand.h"

MoveHeroCommand::MoveHeroCommand(std::shared_ptr<Hero> hero, const sf::Vector2f & delta)
: mHero(hero), mDelta(delta)
{
    
}

MoveHeroCommand::~MoveHeroCommand ()
{
    
}

void MoveHeroCommand::execute ()
{
    if (mHero->surface() != nullptr)
    {
        mHero->adjustVelocity(mDelta);
    }
}

void MoveHeroCommand::undo ()
{
    // This command does not support undo because of the way the Hero
    // clips the move amount and changes direction when it hits an edge.
}
