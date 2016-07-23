//
//  BounceGame.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <random>

#include "Game.h"

class BounceGame : public Game
{
public:
    explicit BounceGame ();
    virtual ~BounceGame ();
    
    virtual void handleInput ();
    virtual void update ();
    virtual void render ();
    
private:
    void moveDot ();
    
    sf::Texture mSphereTexture;
    sf::Vector2u mSphereTextureSize;
    sf::Sprite mDot;
    sf::Vector2f mPositionDelta;
    float randomX;
    float randomY;
    std::mt19937 randomGenerator;
    std::uniform_real_distribution<float> uniformDistribution;
};