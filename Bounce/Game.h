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
    virtual ~Game ();
    
    virtual void handleInput () = 0;
    virtual void update () = 0;
    virtual void render () = 0;
    
    Window * getWindow ();
    
private:
    Window mWindow;
};
