//
//  Game.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include "Window.h"

class Game
{
public:
    explicit Game ();
    ~Game ();
    
    void handleInput ();
    void update ();
    void render ();
    
    Window * getWindow ();
    
private:
    void moveDot ();
    
    Window mWindow;
    sf::Texture mSphereTexture;
};
