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
    virtual ~Game ();
    
    virtual void handleInput () = 0;
    virtual void update () = 0;
    virtual void render () = 0;
    
    Window * getWindow ();
    
    sf::Time elapsed () const;
    void restartClock ();
    
protected:
    Game ();
    Game (const std::string & title, const sf::Vector2u & size);
    
private:
    Window mWindow;
    sf::Clock mClock;
    sf::Time mElapsed;
};
