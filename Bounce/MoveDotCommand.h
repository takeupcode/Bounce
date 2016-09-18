//
//  MoveDotCommand.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include "../EasySFML/Command.h"

#include "Dot.h"

class MoveDotCommand : public Command
{
public:
    MoveDotCommand(std::shared_ptr<Dot> dot, const sf::Vector2f & delta);
    virtual ~MoveDotCommand ();
    
    void execute () override;
    void undo () override;
    
private:
    std::shared_ptr<Dot> mDot;
    sf::Vector2f mDelta;
};
