//
//  Dot.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Window.h"

class Dot
{
public:
    Dot (Window * windowPtr, const sf::Texture & texture, const sf::Vector2f & position);
    ~Dot ();

    void move (const sf::Vector2f delta, float elapsedSeconds);
    
    void draw ();
    
private:
    Window * mWindowPtr;
    sf::Sprite mDot;
    sf::Vector2f mPositionDelta;
    sf::Vector2u mTextureSize;
};
