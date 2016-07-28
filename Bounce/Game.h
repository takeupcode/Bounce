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
    
    virtual void handleInput ();
    virtual void update () = 0;
    virtual void render () = 0;
    virtual void loadBindings () = 0;
    
    bool isDone () const;
    sf::Time elapsed () const;
    void restartClock ();
    bool isFixedFrameReady () const;
    void completeFixedFrame ();
    
protected:
    Game ();
    Game (const std::string & title, const sf::Vector2u & size);
    
    std::shared_ptr<Window> getWindow ();
    const std::shared_ptr<Window> getWindow () const;
    
private:
    const float mFixedFrameTime = 1.0f / 60.0f;
    
    std::shared_ptr<Window> mWindow;
    sf::Clock mClock;
    sf::Time mElapsed;
    sf::Time mFixedFrameTotal;
};
