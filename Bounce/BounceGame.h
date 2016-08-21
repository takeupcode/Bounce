//
//  BounceGame.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <random>
#include <vector>

#include "Game.h"

class Command;
class Dot;
class Window;

class BounceGame : public GameShared<BounceGame>
{
public:
    BounceGame (Director * director);
    virtual ~BounceGame ();
    
    void update () override;
    void render () override;

protected:
    void loadDerivedTriggers () override;

    std::shared_ptr<Window> createMainWindow () const override;
    int mainWindowIdentity () const override;
    
    void notify (EventParameter eventDetails) override;

private:
    const unsigned int MainWindowWidth = 800;
    const unsigned int MainWindowHeight = 600;
    
    sf::Texture mSphereTexture;
    std::shared_ptr<Dot> mDot;
    std::mt19937 randomGenerator;
    std::uniform_real_distribution<float> uniformDistribution;
    std::vector<std::unique_ptr<Command>> mCommands;
    std::shared_ptr<Window> mMainWindow;
};