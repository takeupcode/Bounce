//
//  Dot.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include <math.h>

#include "../EasySFML/Region.h"
#include "../EasySFML/Window.h"

#include "Dot.h"

using namespace std;

Dot::Dot (std::shared_ptr<sf::Texture> texture, const sf::Vector2f & position, const sf::Vector2f & velocity, const sf::Vector2f & acceleration, const sf::Vector2u & bounds)
: Entity(position, velocity, acceleration, {87, 136}, {0.25f, 0.25f}), mBounds(bounds)
{
    mSheet.reset(new SpriteSheet(texture));
    
    AnimationDefinition * animation = mSheet->addAnimation("walk", "walk");
    animation->addFrame(0.15f, {0, 0}, size());
    animation->addFrame(0.15f, {87, 0}, size());
    animation->addFrame(0.15f, {174, 0}, size());
    animation->addFrame(0.15f, {261, 0}, size());
    animation->addFrame(0.15f, {348, 0}, size());
    animation->addFrame(0.15f, {435, 0}, size());
    animation->addFrame(0.15f, {522, 0}, size());
    animation->addFrame(0.15f, {609, 0}, size());
    
    mAnimation.reset(new SpriteAnimation(mSheet, "walk", scale()));
    
    mAnimation->setPosition(position);
}

void Dot::update (float elapsedSeconds)
{
    mVelocity.x += mAcceleration.x;
    mVelocity.y += mAcceleration.y;
    
    if (mVelocity.x > 200.0f)
    {
        mVelocity.x = 200.0f;
    }
    else if (mVelocity.x < -200.0f)
    {
        mVelocity.x = -200.0f;
    }
    
    if (mVelocity.y > 300.0f)
    {
        mVelocity.y = 300.0f;
    }
    else if (mVelocity.y < -300.0f)
    {
        mVelocity.y = -300.0f;
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
