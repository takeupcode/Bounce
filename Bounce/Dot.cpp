//
//  Dot.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "../EasySFML/Window.h"

#include "Dot.h"

using namespace std;

Dot::Dot (std::shared_ptr<sf::Texture> texture, const sf::Vector2f & position, const sf::Vector2u & bounds)
: mPositionDelta(0.0f, 0.0f), mBounds(bounds)
{
    mSheet.reset(new SpriteSheet(texture));
    
    AnimationDefinition * animation = mSheet->addAnimation("walk", "walk");
    animation->addFrame(0.15f, {0, 0}, {87, 136});
    animation->addFrame(0.15f, {87, 0}, {87, 136});
    animation->addFrame(0.15f, {174, 0}, {87, 136});
    animation->addFrame(0.15f, {261, 0}, {87, 136});
    animation->addFrame(0.15f, {348, 0}, {87, 136});
    animation->addFrame(0.15f, {435, 0}, {87, 136});
    animation->addFrame(0.15f, {522, 0}, {87, 136});
    animation->addFrame(0.15f, {609, 0}, {87, 136});
    
    mAnimation.reset(new SpriteAnimation(mSheet, "walk", {0.5f, 0.5f}));
    
    mAnimation->setPosition(position);
}

void Dot::move (const sf::Vector2f delta, float elapsedSeconds)
{
    mPositionDelta += delta;
    
    if (mPositionDelta.x > 500.0f)
    {
        mPositionDelta.x = 500.0f;
    }
    else if (mPositionDelta.x < -500.0f)
    {
        mPositionDelta.x = -500.0f;
    }
    
    if (mPositionDelta.y > 500.0f)
    {
        mPositionDelta.y = 500.0f;
    }
    else if (mPositionDelta.y < -500.0f)
    {
        mPositionDelta.y = -500.0f;
    }

    if ((mAnimation->position().x + mAnimation->size().x / 2 > mBounds.x &&
         mPositionDelta.x > 0) ||
        (mAnimation->position().x - mAnimation->size().x / 2 < 0 &&
         mPositionDelta.x < 0))
    {
        mPositionDelta.x = -mPositionDelta.x;
    }
    
    if ((mAnimation->position().y > mBounds.y &&
         mPositionDelta.y > 0) ||
        (mAnimation->position().y - mAnimation->size().y < 0 &&
         mPositionDelta.y < 0))
    {
        mPositionDelta.y = -mPositionDelta.y;
    }
    
    mAnimation->move(mPositionDelta * elapsedSeconds);
    mAnimation->update(elapsedSeconds);
}

void Dot::draw (Window * window)
{
    mAnimation->draw(window);
}
