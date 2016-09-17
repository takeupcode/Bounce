//
//  Dot.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "../EasySFML/Region.h"
#include "../EasySFML/Window.h"

#include "Dot.h"

using namespace std;

Dot::Dot (std::shared_ptr<sf::Texture> texture, const sf::Vector2f & position, const sf::Vector2u & bounds)
: Entity(position, {0.0f, 0.0f}, {87, 136}, {0.5f, 0.5f}), mBounds(bounds)
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

void Dot::move (const sf::Vector2f delta, float elapsedSeconds)
{
    sf::Vector2f newVelocity =  velocity() + delta;
    
    if (newVelocity.x > 500.0f)
    {
        newVelocity.x = 500.0f;
    }
    else if (newVelocity.x < -500.0f)
    {
        newVelocity.x = -500.0f;
    }
    
    if (newVelocity.y > 500.0f)
    {
        newVelocity.y = 500.0f;
    }
    else if (newVelocity.y < -500.0f)
    {
        newVelocity.y = -500.0f;
    }

    if ((position().x + mAnimation->scaledSize().x / 2 > mBounds.x &&
         newVelocity.x > 0) ||
        (position().x - mAnimation->scaledSize().x / 2 < 0 &&
         newVelocity.x < 0))
    {
        newVelocity.x = -newVelocity.x;
    }
    
    if ((position().y > mBounds.y &&
         newVelocity.y > 0) ||
        (position().y - mAnimation->scaledSize().y < 0 &&
         newVelocity.y < 0))
    {
        newVelocity.y = -newVelocity.y;
    }
    
    setPosition(position() + newVelocity * elapsedSeconds);
    setVelocity(newVelocity);
    
    mAnimation->setPosition(position());
    mAnimation->update(elapsedSeconds);
}

void Dot::draw (Window * window)
{
    mAnimation->draw(window);
}
