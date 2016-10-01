//
//  Dot.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include <math.h>

#include "../EasySFML/Director.h"
#include "../EasySFML/Region.h"
#include "../EasySFML/TextureManager.h"
#include "../EasySFML/Window.h"

#include "Dot.h"

#include "OS/Mac/ResourcePath.hpp"

using namespace std;

const string Dot::Walk = "walk";
const string Dot::WalkEast = "walkEast";
const string Dot::WalkWest = "walkWest";
const string Dot::Idle = "idle";
const string Dot::IdleEast = "idleEast";
const string Dot::IdleWest = "idleWest";

Dot::Dot (Director * director, const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & acceleration, const sf::Vector2f & bounds)
: Entity(director, position, velocity, acceleration, {0.5f, 0.5f}), mBounds(bounds), mDirection(Direction::East), mIdle(true)
{
    director->textureManager()->loadTexture(Walk, resourcePath() + "HeroWalk.png");
    director->textureManager()->loadTexture(Idle, resourcePath() + "HeroIdle.png");
    
    shared_ptr<SpriteSheet> idleSheet(new SpriteSheet(Idle, director->textureManager()->texture(Idle)));
    
    AnimationDefinition * animation = idleSheet->addAnimation(IdleEast, IdleEast);
    animation->addFrame(0.23f, {0, 0}, {72, 130});
    animation->addFrame(0.23f, {72, 0}, {72, 130});
    animation->addFrame(0.62f, {144, 0}, {72, 130});
    animation->addFrame(0.31f, {216, 0}, {72, 130});
    animation->addFrame(0.25f, {288, 0}, {72, 130});
    animation->addFrame(0.57f, {360, 0}, {72, 130});
    animation->addFrame(0.23f, {432, 0}, {72, 130});
    animation->addFrame(0.15f, {504, 0}, {72, 130});
    animation->addFrame(0.23f, {0, 130}, {72, 130});
    animation->addFrame(0.35f, {72, 130}, {72, 130});
    animation->addFrame(0.15f, {144, 130}, {72, 130});
    animation->addFrame(0.12f, {216, 130}, {72, 130});
    animation->addFrame(0.31f, {288, 130}, {72, 130});
    animation->addFrame(0.25f, {360, 130}, {72, 130});
    animation->addFrame(0.57f, {432, 130}, {72, 130});
    animation->addFrame(0.23f, {504, 130}, {72, 130});
    
    mAnimation.reset(new SpriteAnimation(idleSheet, IdleEast, scale()));
    setSize(mAnimation->size());
    
    animation = idleSheet->addAnimation(IdleWest, IdleWest);
    animation->addFrame(0.23f, {0, 260}, {72, 130});
    animation->addFrame(0.23f, {72, 260}, {72, 130});
    animation->addFrame(0.62f, {144, 260}, {72, 130});
    animation->addFrame(0.31f, {216, 260}, {72, 130});
    animation->addFrame(0.25f, {288, 260}, {72, 130});
    animation->addFrame(0.57f, {360, 260}, {72, 130});
    animation->addFrame(0.23f, {432, 260}, {72, 130});
    animation->addFrame(0.15f, {504, 260}, {72, 130});
    animation->addFrame(0.23f, {0, 390}, {72, 130});
    animation->addFrame(0.35f, {72, 390}, {72, 130});
    animation->addFrame(0.15f, {144, 390}, {72, 130});
    animation->addFrame(0.12f, {216, 390}, {72, 130});
    animation->addFrame(0.31f, {288, 390}, {72, 130});
    animation->addFrame(0.25f, {360, 390}, {72, 130});
    animation->addFrame(0.57f, {432, 390}, {72, 130});
    animation->addFrame(0.23f, {504, 390}, {72, 130});
    
    mAnimation->addAnimation(idleSheet, IdleWest);
    
    shared_ptr<SpriteSheet> walkSheet(new SpriteSheet(Walk, director->textureManager()->texture(Walk)));
    
    animation = walkSheet->addAnimation(WalkEast, WalkEast);
    animation->addFrame(0.15f, {0, 0}, {87, 136});
    animation->addFrame(0.15f, {87, 0}, {87, 136});
    animation->addFrame(0.15f, {174, 0}, {87, 136});
    animation->addFrame(0.15f, {261, 0}, {87, 136});
    animation->addFrame(0.15f, {348, 0}, {87, 136});
    animation->addFrame(0.15f, {435, 0}, {87, 136});
    animation->addFrame(0.15f, {522, 0}, {87, 136});
    animation->addFrame(0.15f, {609, 0}, {87, 136});
    
    mAnimation->addAnimation(walkSheet, WalkEast);
    
    animation = walkSheet->addAnimation(WalkWest, WalkWest);
    animation->addFrame(0.15f, {0, 136}, {87, 136});
    animation->addFrame(0.15f, {87, 136}, {87, 136});
    animation->addFrame(0.15f, {174, 136}, {87, 136});
    animation->addFrame(0.15f, {261, 136}, {87, 136});
    animation->addFrame(0.15f, {348, 136}, {87, 136});
    animation->addFrame(0.15f, {435, 136}, {87, 136});
    animation->addFrame(0.15f, {522, 136}, {87, 136});
    animation->addFrame(0.15f, {609, 136}, {87, 136});
    
    mAnimation->addAnimation(walkSheet, WalkWest);
    
    mAnimation->setPosition(position);
}

void Dot::update (float elapsedSeconds)
{
    mVelocity.x += mAcceleration.x;
    mVelocity.y += mAcceleration.y;
    
    if (mSurfaceTile)
    {
        float friction = 0.0f;
        FrameTag * tag = mSurfaceTile->tag("friction");
        if (tag && tag->type() == FrameTag::TagType::FloatTag)
        {
            friction = tag->floatValue();
            if (mVelocity.x > 0)
            {
                mVelocity.x += friction;
                if (mVelocity.x < 0)
                {
                    mVelocity.x = 0;
                }
            }
            else if (mVelocity.x < 0)
            {
                mVelocity.x -= friction;
                if (mVelocity.x > 0)
                {
                    mVelocity.x = 0;
                }
            }
        }
    }
    
    if (mVelocity.x > 200.0f)
    {
        mVelocity.x = 200.0f;
    }
    else if (mVelocity.x < -200.0f)
    {
        mVelocity.x = -200.0f;
    }
    
    if (mVelocity.y > 400.0f)
    {
        mVelocity.y = 400.0f;
    }
    else if (mVelocity.y < -400.0f)
    {
        mVelocity.y = -400.0f;
    }
    
    if (mVelocity.x > 0)
    {
        if (mDirection != Direction::East || mIdle)
        {
            mAnimation->setAnimation(WalkEast);
            setSize(mAnimation->size());
            mDirection = Direction::East;
            mIdle = false;
        }
    }
    else if (mVelocity.x < 0)
    {
        if (mDirection != Direction::West || mIdle)
        {
            mAnimation->setAnimation(WalkWest);
            setSize(mAnimation->size());
            mDirection = Direction::West;
            mIdle = false;
        }
    }
    else
    {
        if (!mIdle)
        {
            if (mDirection == Direction::East)
            {
                mAnimation->setAnimation(IdleEast);
            }
            else if (mDirection == Direction::West)
            {
                mAnimation->setAnimation(IdleWest);
            }
            setSize(mAnimation->size());
            mIdle = true;
        }
    }

    mPosition.x += mVelocity.x * elapsedSeconds;
    mPosition.y += mVelocity.y * elapsedSeconds;
    
    // Make sure that collisions can happen each update by ensuring
    // this object tries to drop at least one pixel each frame.
    mPosition.y += 1;

    if (mPosition.x + mAnimation->scaledSize().x / 2 > mBounds.x)
    {
        mPosition.x = mBounds.x - mAnimation->scaledSize().x / 2;
        mVelocity.x = 0;
    }
    else if (mPosition.x - mAnimation->scaledSize().x / 2 < 0)
    {
        mPosition.x = mAnimation->scaledSize().x / 2;
        mVelocity.x = 0;
    }
    
    if (mPosition.y > mBounds.y)
    {
        mPosition.y = mBounds.y;
        mVelocity.y = 0;
    }
    else if (mPosition.y - mAnimation->scaledSize().y < 0 )
    {
        mPosition.y = mAnimation->scaledSize().y;
    }
    
    mAnimation->update(elapsedSeconds);
}

void Dot::draw (Window * window)
{
    mAnimation->setPosition(mPosition);
    mAnimation->draw(window);
}
