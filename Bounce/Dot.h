//
//  Dot.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "../EasySFML/SpriteAnimation.h"
#include "../EasySFML/SpriteSheet.h"

class Window;

class Dot
{
public:
    Dot (std::shared_ptr<sf::Texture> texture, const sf::Vector2f & position, const sf::Vector2u & bounds);

    void move (const sf::Vector2f delta, float elapsedSeconds);
    
    void draw (Window * window);
    
private:
    std::shared_ptr<SpriteSheet> mSheet;
    std::shared_ptr<SpriteAnimation> mAnimation;
    sf::Vector2f mPositionDelta;
    sf::Vector2u mBounds;
};
