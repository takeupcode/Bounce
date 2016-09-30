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

using namespace std;

const string Dot::Walk = "walk";
const string Dot::WalkEast = "walkEast";
const string Dot::WalkWest = "walkWest";

Dot::Dot (Director * director, const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & acceleration, const sf::Vector2f & bounds)
: Entity(director, position, velocity, acceleration, {87, 136}, {0.25f, 0.25f}), mBounds(bounds), mDirection(Direction::East)
{

    mSheet.reset(new SpriteSheet(director->textureManager()->texture(Walk)));
    
    AnimationDefinition * animation = mSheet->addAnimation(WalkEast, WalkEast);
    animation->addFrame(0.15f, {0, 0}, size());
    animation->addFrame(0.15f, {87, 0}, size());
    animation->addFrame(0.15f, {174, 0}, size());
    animation->addFrame(0.15f, {261, 0}, size());
    animation->addFrame(0.15f, {348, 0}, size());
    animation->addFrame(0.15f, {435, 0}, size());
    animation->addFrame(0.15f, {522, 0}, size());
    animation->addFrame(0.15f, {609, 0}, size());
    
    animation = mSheet->addAnimation(WalkWest, WalkWest);
    animation->addFrame(0.15f, {0, 136}, size());
    animation->addFrame(0.15f, {87, 136}, size());
    animation->addFrame(0.15f, {174, 136}, size());
    animation->addFrame(0.15f, {261, 136}, size());
    animation->addFrame(0.15f, {348, 136}, size());
    animation->addFrame(0.15f, {435, 136}, size());
    animation->addFrame(0.15f, {522, 136}, size());
    animation->addFrame(0.15f, {609, 136}, size());
    
    mAnimation.reset(new SpriteAnimation(mSheet, WalkEast, scale()));
    
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
    
    if (mVelocity.x > 100.0f)
    {
        mVelocity.x = 100.0f;
    }
    else if (mVelocity.x < -100.0f)
    {
        mVelocity.x = -100.0f;
    }
    
    if (mVelocity.y > 300.0f)
    {
        mVelocity.y = 300.0f;
    }
    else if (mVelocity.y < -300.0f)
    {
        mVelocity.y = -300.0f;
    }
    
    if (mVelocity.x > 0)
    {
        if (mDirection != Direction::East)
        {
            mAnimation->setAnimation(WalkEast);
            mDirection = Direction::East;
        }
    }
    else if (mVelocity.x < 0)
    {
        if (mDirection != Direction::West)
        {
            mAnimation->setAnimation(WalkWest);
            mDirection = Direction::West;
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
