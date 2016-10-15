//
//  Hero.h
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

#include "HeroStateFalling.h"
#include "HeroStateIdle.h"
#include "HeroStateJumping.h"
#include "HeroStateRunning.h"
#include "HeroStateSkidding.h"
#include "HeroStateWalking.h"

class Window;
class Region;

class Hero : public Entity
{
public:
    const static int CommandWalkEast = 1;
    const static int CommandWalkWest = 2;
    const static int CommandRunEast = 3;
    const static int CommandRunWest = 4;
    const static int CommandJump = 5;
    
    Hero (Director * director, const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & acceleration, const sf::Vector2f & bounds);
    
    void handleCommand (int command) override;

    void update (float elapsedSeconds) override;
    
    void draw (Window * window) override;
    
private:
    friend class HeroStateFalling;
    friend class HeroStateIdle;
    friend class HeroStateInAir;
    friend class HeroStateJumping;
    friend class HeroStateMaster;
    friend class HeroStateOnGround;
    friend class HeroStateRunning;
    friend class HeroStateSkidding;
    friend class HeroStateWalking;
    
    static HeroStateFalling mStateFalling;
    static HeroStateIdle mStateIdle;
    static HeroStateJumping mStateJumping;
    static HeroStateRunning mStateRunning;
    static HeroStateSkidding mStateSkidding;
    static HeroStateWalking mStateWalking;
    
    static const std::string HeroId;
    static const std::string WalkEast;
    static const std::string WalkWest;
    static const std::string IdleEast;
    static const std::string IdleWest;
    static const std::string JumpStartEast;
    static const std::string JumpStartWest;
    static const std::string JumpLoopEast;
    static const std::string JumpLoopWest;
    static const std::string FallStartEast;
    static const std::string FallStartWest;
    static const std::string FallLoopEast;
    static const std::string FallLoopWest;
    static const std::string RunEast;
    static const std::string RunWest;
    static const std::string SkidEast;
    static const std::string SkidWest;
    
    std::shared_ptr<SpriteAnimation> mAnimation;
    sf::Vector2f mBounds;
    Direction mDirection;
    bool mIdle;
};
