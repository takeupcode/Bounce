//
//  Dot.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <SFML/Graphics.hpp>

class Window;

class Dot
{
public:
    Dot (const sf::Texture * texture, const sf::Vector2f & position, const sf::Vector2u & bounds);
    ~Dot ();

    void move (const sf::Vector2f delta, float elapsedSeconds);
    
    void draw (Window * window);
    
private:
    sf::Sprite mDot;
    sf::Vector2f mPositionDelta;
    sf::Vector2u mTextureSize;
    sf::Vector2u mBounds;
};
