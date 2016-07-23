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
    
    bool isDone () const;
    sf::Time elapsed () const;
    void restartClock ();
    bool isFixedFrameReady () const;
    void completeFixedFrame ();
    
protected:
    Game ();
    Game (const std::string & title, const sf::Vector2u & size);
    
    Window * getWindow ();
    const Window * getWindow () const;
    
private:
    const float mFixedFrameTime = 1.0f / 60.0f;
    
    Window mWindow;
    sf::Clock mClock;
    sf::Time mElapsed;
    sf::Time mFixedFrameTotal;
};
