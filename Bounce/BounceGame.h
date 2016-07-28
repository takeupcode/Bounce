//
//  BounceGame.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <random>
#include <vector>

#include "BindingManager.h"
#include "Command.h"
#include "Game.h"
#include "Dot.h"

class BounceGame : public Game, public std::enable_shared_from_this<BounceGame>, public EventSubscriber<Binding::BindingEventParameter>
{
public:
    BounceGame ();
    virtual ~BounceGame ();

    void update () override;
    void render () override;
    void loadBindings () override;
    
    void notify (Binding::BindingEventParameter eventDetails) override;
    
private:
    sf::Texture mSphereTexture;
    Dot * mDotPtr;
    std::mt19937 randomGenerator;
    std::uniform_real_distribution<float> uniformDistribution;
    std::vector<Command *> mCommands;
};