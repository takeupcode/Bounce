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

const string Dot::Hero = "hero";
const string Dot::WalkEast = "walkEast";
const string Dot::WalkWest = "walkWest";
const string Dot::IdleEast = "idleEast";
const string Dot::IdleWest = "idleWest";

Dot::Dot (Director * director, const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & acceleration, const sf::Vector2f & bounds)
: Entity(director, position, velocity, acceleration, {0.25f, 0.25f}), mBounds(bounds), mDirection(Direction::East), mIdle(true)
{
    director->textureManager()->loadTexture(Hero, resourcePath() + "Hero.png");
    
    shared_ptr<SpriteSheet> heroSheet(new SpriteSheet(Hero, resourcePath() + "Hero.json", director->textureManager()->texture(Hero)));
    
    AnimationDefinition * animation = heroSheet->addAnimation(IdleEast, IdleEast);
    animation->addFrame("Hero/Idle/Right-000", 0.23f);
    animation->addFrame("Hero/Idle/Right-001", 0.23f);
    animation->addFrame("Hero/Idle/Right-002", 0.62f);
    animation->addFrame("Hero/Idle/Right-003", 0.31f);
    animation->addFrame("Hero/Idle/Right-004", 0.25f);
    animation->addFrame("Hero/Idle/Right-005", 0.57f);
    animation->addFrame("Hero/Idle/Right-006", 0.23f);
    animation->addFrame("Hero/Idle/Right-007", 0.15f);
    animation->addFrame("Hero/Idle/Right-008", 0.23f);
    animation->addFrame("Hero/Idle/Right-009", 0.35f);
    animation->addFrame("Hero/Idle/Right-010", 0.15f);
    animation->addFrame("Hero/Idle/Right-011", 0.12f);
    animation->addFrame("Hero/Idle/Right-012", 0.31f);
    animation->addFrame("Hero/Idle/Right-013", 0.25f);
    animation->addFrame("Hero/Idle/Right-014", 0.57f);
    animation->addFrame("Hero/Idle/Right-015", 0.23f);
    
    mAnimation.reset(new SpriteAnimation(heroSheet, IdleEast, scale()));
    setSize(mAnimation->size());
    
    animation = heroSheet->addAnimation(IdleWest, IdleWest);
    animation->addFrame("Hero/Idle/Left-000", 0.23f);
    animation->addFrame("Hero/Idle/Left-001", 0.23f);
    animation->addFrame("Hero/Idle/Left-002", 0.62f);
    animation->addFrame("Hero/Idle/Left-003", 0.31f);
    animation->addFrame("Hero/Idle/Left-004", 0.25f);
    animation->addFrame("Hero/Idle/Left-005", 0.57f);
    animation->addFrame("Hero/Idle/Left-006", 0.23f);
    animation->addFrame("Hero/Idle/Left-007", 0.15f);
    animation->addFrame("Hero/Idle/Left-008", 0.23f);
    animation->addFrame("Hero/Idle/Left-009", 0.35f);
    animation->addFrame("Hero/Idle/Left-010", 0.15f);
    animation->addFrame("Hero/Idle/Left-011", 0.12f);
    animation->addFrame("Hero/Idle/Left-012", 0.31f);
    animation->addFrame("Hero/Idle/Left-013", 0.25f);
    animation->addFrame("Hero/Idle/Left-014", 0.57f);
    animation->addFrame("Hero/Idle/Left-015", 0.23f);
    
    mAnimation->addAnimation(heroSheet, IdleWest);
    
    animation = heroSheet->addAnimation(WalkEast, WalkEast);
    animation->addFrame("Hero/Walk/Right-000", 0.15f);
    animation->addFrame("Hero/Walk/Right-001", 0.15f);
    animation->addFrame("Hero/Walk/Right-002", 0.15f);
    animation->addFrame("Hero/Walk/Right-003", 0.15f);
    animation->addFrame("Hero/Walk/Right-004", 0.15f);
    animation->addFrame("Hero/Walk/Right-005", 0.15f);
    animation->addFrame("Hero/Walk/Right-006", 0.15f);
    animation->addFrame("Hero/Walk/Right-007", 0.15f);
    
    mAnimation->addAnimation(heroSheet, WalkEast);
    
    animation = heroSheet->addAnimation(WalkWest, WalkWest);
    animation->addFrame("Hero/Walk/Left-000", 0.15f);
    animation->addFrame("Hero/Walk/Left-001", 0.15f);
    animation->addFrame("Hero/Walk/Left-002", 0.15f);
    animation->addFrame("Hero/Walk/Left-003", 0.15f);
    animation->addFrame("Hero/Walk/Left-004", 0.15f);
    animation->addFrame("Hero/Walk/Left-005", 0.15f);
    animation->addFrame("Hero/Walk/Left-006", 0.15f);
    animation->addFrame("Hero/Walk/Left-007", 0.15f);
    
    mAnimation->addAnimation(heroSheet, WalkWest);
    
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
