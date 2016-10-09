//
//  MoveHeroCommand.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include "../EasySFML/Command.h"

#include "Hero.h"

class MoveHeroCommand : public Command
{
public:
    MoveHeroCommand(std::shared_ptr<Hero> hero, const sf::Vector2f & delta);
    virtual ~MoveHeroCommand ();
    
    void execute () override;
    void undo () override;
    
private:
    std::shared_ptr<Hero> mHero;
    sf::Vector2f mDelta;
};
