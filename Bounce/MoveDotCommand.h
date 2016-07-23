//
//  MoveDotCommand.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include "Command.h"
#include "Dot.h"

class MoveDotCommand : public Command
{
public:
    MoveDotCommand(Dot * dotPtr, const sf::Vector2f & delta, float elapsedSeconds);
    virtual ~MoveDotCommand ();
    
    void execute () override;
    void undo () override;
    
private:
    Dot * mDotPtr;
    sf::Vector2f mDelta;
    float mElapsedSeconds;
};
