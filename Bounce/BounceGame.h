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

#include "../EasySFML/Game.h"

class Command;
class Dot;
class Window;

class BounceGame : public Game
{
public:
    explicit BounceGame (Director * director);
    virtual ~BounceGame ();

protected:
    void registerScenes () override;
    
    void setInitialScenes () override;

    std::shared_ptr<Window> createMainWindow () const override;
    int mainWindowIdentity () const override;

private:
    const unsigned int MainWindowWidth = 768;
    const unsigned int MainWindowHeight = 640;
};