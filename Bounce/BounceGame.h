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

#include "Command.h"
#include "Game.h"
#include "Dot.h"

class BounceGame : public Game
{
public:
    explicit BounceGame ();
    virtual ~BounceGame ();
    
    virtual void handleInput ();
    virtual void update ();
    virtual void render ();
    
private:
    sf::Texture mSphereTexture;
    Dot * mDotPtr;
    float randomX;
    float randomY;
    std::mt19937 randomGenerator;
    std::uniform_real_distribution<float> uniformDistribution;
    std::vector<Command *> mCommands;
};