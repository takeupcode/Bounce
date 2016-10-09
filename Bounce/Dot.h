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

#include "../EasySFML/Direction.h"
#include "../EasySFML/Entity.h"
#include "../EasySFML/SpriteAnimation.h"
#include "../EasySFML/SpriteSheet.h"

class Window;
class Region;

class Dot : public Entity
{
public:
    static const std::string Hero;
    static const std::string WalkEast;
    static const std::string WalkWest;
    static const std::string IdleEast;
    static const std::string IdleWest;
    
    Dot (Director * director, const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & acceleration, const sf::Vector2f & bounds);

    void update (float elapsedSeconds) override;
    
    void draw (Window * window) override;
    
private:
    std::shared_ptr<SpriteAnimation> mAnimation;
    sf::Vector2f mBounds;
    Direction mDirection;
    bool mIdle;
};
