//
//  MoveDotCommand.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "MoveDotCommand.h"

MoveDotCommand::MoveDotCommand(Dot * dotPtr, const sf::Vector2f & delta, float elapsedSeconds)
: mDotPtr(dotPtr), mDelta(delta), mElapsedSeconds(elapsedSeconds)
{
    
}

MoveDotCommand::~MoveDotCommand ()
{
    
}

void MoveDotCommand::execute ()
{
    mDotPtr->move(mDelta, mElapsedSeconds);
}

void MoveDotCommand::undo ()
{
    // This command does not support undo because of the way the dot
    // clips the move amount and changes direction when it hits an edge.
}
