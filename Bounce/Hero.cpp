//
//  Hero.cpp
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

#include "Hero.h"

#include "OS/Mac/ResourcePath.hpp"

using namespace std;

const string Hero::HeroId = "hero";
const string Hero::WalkEast = "walkEast";
const string Hero::WalkWest = "walkWest";
const string Hero::IdleEast = "idleEast";
const string Hero::IdleWest = "idleWest";
const string Hero::JumpStartEast = "jumpStartEast";
const string Hero::JumpStartWest = "jumpStartWest";
const string Hero::JumpLoopEast = "jumpLoopEast";
const string Hero::JumpLoopWest = "jumpLoopWest";
const string Hero::FallStartEast = "fallStartEast";
const string Hero::FallStartWest = "fallStartWest";
const string Hero::FallLoopEast = "fallLoopEast";
const string Hero::FallLoopWest = "fallLoopWest";
const string Hero::RunEast = "runEast";
const string Hero::RunWest = "runWest";
const string Hero::SkidEast = "skidEast";
const string Hero::SkidWest = "skidWest";

Hero::Hero (Director * director, const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & acceleration, const sf::Vector2f & bounds)
: Entity(director, position, velocity, acceleration, {0.25f, 0.25f}), mBounds(bounds), mDirection(Direction::East), mIdle(true)
{
    director->textureManager()->loadTexture(HeroId, resourcePath() + "Hero.png");
    
    shared_ptr<SpriteSheet> heroSheet(new SpriteSheet(HeroId, resourcePath() + "Hero.json", director->textureManager()->texture(HeroId)));
    
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
    mAnimation->setPosition(position);
    
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
    
    animation = heroSheet->addAnimation(JumpStartEast, JumpLoopEast);
    animation->addFrame("Hero/JumpStart/Right-000", 0.09f);
    animation->addFrame("Hero/JumpStart/Right-001", 0.27f);
    animation->addFrame("Hero/JumpStart/Right-002", 0.12f);
    
    mAnimation->addAnimation(heroSheet, JumpStartEast);
    
    animation = heroSheet->addAnimation(JumpStartWest, JumpLoopWest);
    animation->addFrame("Hero/JumpStart/Left-000", 0.09f);
    animation->addFrame("Hero/JumpStart/Left-001", 0.27f);
    animation->addFrame("Hero/JumpStart/Left-002", 0.12f);
    
    mAnimation->addAnimation(heroSheet, JumpStartWest);
    
    animation = heroSheet->addAnimation(JumpLoopEast, JumpLoopEast);
    animation->addFrame("Hero/JumpLoop/Right-000", 0.12f);
    animation->addFrame("Hero/JumpLoop/Right-001", 0.12f);
    animation->addFrame("Hero/JumpLoop/Right-002", 0.12f);
    animation->addFrame("Hero/JumpLoop/Right-003", 0.12f);
    animation->addFrame("Hero/JumpLoop/Right-004", 0.12f);
    animation->addFrame("Hero/JumpLoop/Right-005", 0.13f);
    
    mAnimation->addAnimation(heroSheet, JumpLoopEast);
    
    animation = heroSheet->addAnimation(JumpLoopWest, JumpLoopWest);
    animation->addFrame("Hero/JumpLoop/Left-000", 0.12f);
    animation->addFrame("Hero/JumpLoop/Left-001", 0.12f);
    animation->addFrame("Hero/JumpLoop/Left-002", 0.12f);
    animation->addFrame("Hero/JumpLoop/Left-003", 0.12f);
    animation->addFrame("Hero/JumpLoop/Left-004", 0.12f);
    animation->addFrame("Hero/JumpLoop/Left-005", 0.13f);
    
    mAnimation->addAnimation(heroSheet, JumpLoopWest);
    
    animation = heroSheet->addAnimation(FallStartEast, FallLoopEast);
    animation->addFrame("Hero/FallStart/Right-000", 0.19f);
    animation->addFrame("Hero/FallStart/Right-001", 0.18f);
    animation->addFrame("Hero/FallStart/Right-002", 0.15f);
    
    mAnimation->addAnimation(heroSheet, FallStartEast);
    
    animation = heroSheet->addAnimation(FallStartWest, FallLoopWest);
    animation->addFrame("Hero/FallStart/Left-000", 0.19f);
    animation->addFrame("Hero/FallStart/Left-001", 0.18f);
    animation->addFrame("Hero/FallStart/Left-002", 0.15f);
    
    mAnimation->addAnimation(heroSheet, FallStartWest);
    
    animation = heroSheet->addAnimation(FallLoopEast, FallLoopEast);
    animation->addFrame("Hero/FallLoop/Right-000", 0.12f);
    animation->addFrame("Hero/FallLoop/Right-001", 0.12f);
    animation->addFrame("Hero/FallLoop/Right-002", 0.12f);
    animation->addFrame("Hero/FallLoop/Right-003", 0.13f);
    
    mAnimation->addAnimation(heroSheet, FallLoopEast);
    
    animation = heroSheet->addAnimation(FallLoopWest, FallLoopWest);
    animation->addFrame("Hero/FallLoop/Left-000", 0.12f);
    animation->addFrame("Hero/FallLoop/Left-001", 0.12f);
    animation->addFrame("Hero/FallLoop/Left-002", 0.12f);
    animation->addFrame("Hero/FallLoop/Left-003", 0.13f);
    
    mAnimation->addAnimation(heroSheet, FallLoopWest);
    
    animation = heroSheet->addAnimation(RunEast, RunEast);
    animation->addFrame("Hero/Idle/Right-000", 0.12f);
    animation->addFrame("Hero/Idle/Right-001", 0.12f);
    animation->addFrame("Hero/Idle/Right-002", 0.12f);
    animation->addFrame("Hero/Idle/Right-003", 0.12f);
    animation->addFrame("Hero/Idle/Right-004", 0.12f);
    animation->addFrame("Hero/Idle/Right-005", 0.12f);
    animation->addFrame("Hero/Idle/Right-006", 0.12f);
    animation->addFrame("Hero/Idle/Right-007", 0.12f);
    animation->addFrame("Hero/Idle/Right-008", 0.12f);
    animation->addFrame("Hero/Idle/Right-009", 0.12f);
    
    mAnimation->addAnimation(heroSheet, RunEast);
    
    animation = heroSheet->addAnimation(RunWest, RunWest);
    animation->addFrame("Hero/Idle/Left-000", 0.12f);
    animation->addFrame("Hero/Idle/Left-001", 0.12f);
    animation->addFrame("Hero/Idle/Left-002", 0.12f);
    animation->addFrame("Hero/Idle/Left-003", 0.12f);
    animation->addFrame("Hero/Idle/Left-004", 0.12f);
    animation->addFrame("Hero/Idle/Left-005", 0.12f);
    animation->addFrame("Hero/Idle/Left-006", 0.12f);
    animation->addFrame("Hero/Idle/Left-007", 0.12f);
    animation->addFrame("Hero/Idle/Left-008", 0.12f);
    animation->addFrame("Hero/Idle/Left-009", 0.12f);
    
    mAnimation->addAnimation(heroSheet, RunWest);
    
    animation = heroSheet->addAnimation(SkidEast, IdleEast);
    animation->addFrame("Hero/Idle/Right-000", 0.06f);
    animation->addFrame("Hero/Idle/Right-001", 0.06f);
    animation->addFrame("Hero/Idle/Right-002", 0.06f);
    animation->addFrame("Hero/Idle/Right-003", 0.06f);
    animation->addFrame("Hero/Idle/Right-004", 0.06f);
    animation->addFrame("Hero/Idle/Right-005", 0.06f);
    animation->addFrame("Hero/Idle/Right-006", 0.06f);
    animation->addFrame("Hero/Idle/Right-007", 0.06f);
    animation->addFrame("Hero/Idle/Right-008", 0.06f);
    animation->addFrame("Hero/Idle/Right-009", 0.08f);
    animation->addFrame("Hero/Idle/Right-010", 0.24f);
    animation->addFrame("Hero/Idle/Right-011", 0.16f);
    animation->addFrame("Hero/Idle/Right-012", 0.15f);
    animation->addFrame("Hero/Idle/Right-013", 0.04f);
    animation->addFrame("Hero/Idle/Right-014", 0.04f);
    
    mAnimation->addAnimation(heroSheet, SkidEast);
    
    animation = heroSheet->addAnimation(SkidWest, IdleWest);
    animation->addFrame("Hero/Idle/Left-000", 0.06f);
    animation->addFrame("Hero/Idle/Left-001", 0.06f);
    animation->addFrame("Hero/Idle/Left-002", 0.06f);
    animation->addFrame("Hero/Idle/Left-003", 0.06f);
    animation->addFrame("Hero/Idle/Left-004", 0.06f);
    animation->addFrame("Hero/Idle/Left-005", 0.06f);
    animation->addFrame("Hero/Idle/Left-006", 0.06f);
    animation->addFrame("Hero/Idle/Left-007", 0.06f);
    animation->addFrame("Hero/Idle/Left-008", 0.06f);
    animation->addFrame("Hero/Idle/Left-009", 0.08f);
    animation->addFrame("Hero/Idle/Left-010", 0.24f);
    animation->addFrame("Hero/Idle/Left-011", 0.16f);
    animation->addFrame("Hero/Idle/Left-012", 0.15f);
    animation->addFrame("Hero/Idle/Left-013", 0.04f);
    animation->addFrame("Hero/Idle/Left-014", 0.04f);
    
    mAnimation->addAnimation(heroSheet, SkidWest);
}

void Hero::update (float elapsedSeconds)
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

void Hero::draw (Window * window)
{
    mAnimation->setPosition(mPosition);
    mAnimation->draw(window);
}
