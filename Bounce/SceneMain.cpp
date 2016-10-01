//
//  SceneMain.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include <stdexcept>

#include "../EasySFML/Director.h"
#include "../EasySFML/EventManager.h"
#include "../EasySFML/Region.h"
#include "../EasySFML/SceneManager.h"
#include "../EasySFML/TextureManager.h"
#include "../EasySFML/Trigger.h"
#include "../EasySFML/Window.h"

#include "BounceGame.h"
#include "MoveDotCommand.h"
#include "SceneIdentities.h"
#include "SceneMain.h"
#include "WindowIdentities.h"

#include "OS/Mac/ResourcePath.hpp"

using namespace std;

const string SceneMain::MoveCharacterLeft = "MoveCharacterLeft";
const string SceneMain::MoveCharacterRight = "MoveCharacterRight";
const string SceneMain::MoveCharacterUp = "MoveCharacterUp";
const string SceneMain::MoveCharacterDown = "MoveCharacterDown";

SceneMain::SceneMain (Director * director, int identity, std::shared_ptr<Window> window, bool transparent, bool modal)
: Scene(director, identity, window, transparent, modal), uniformDistribution(-10.0f, 10.0f)
{
}

void SceneMain::created ()
{
    Scene::created();
    
    if (hasBeenRecreated())
    {
        return;
    }
    
    string walk = "walk";
    string idle = "idle";
    string tiles = "tiles";
    director()->textureManager()->loadTexture(tiles, resourcePath() + "tiles.png");

    mTileSheet.reset(new SpriteSheet(tiles, director()->textureManager()->texture(tiles)));
    AnimationDefinition * animation = mTileSheet->addAnimation("grass-large", "");
    FrameDefinition * frame = animation->addFrame(1.0f, {0, 0}, {48, 48});
    frame->addTag("friction", -5.0f);
    
    mRegion.reset(new Region(mTileSheet, {1.0f, 1.0f}, {48, 48}, 32, 13));
    mRegion->addTileType("grass-large", "grass-large");
    mRegion->setTile(0, 0, "grass-large");
    mRegion->setTile(15, 0, "grass-large");
    mRegion->setTile(0, 10, "grass-large");
    mRegion->setTile(0, 11, "grass-large");
    mRegion->setTile(0, 12, "grass-large");
    mRegion->setTile(1, 11, "grass-large");
    mRegion->setTile(1, 12, "grass-large");
    mRegion->setTile(2, 11, "grass-large");
    mRegion->setTile(2, 12, "grass-large");
    mRegion->setTile(3, 12, "grass-large");
    mRegion->setTile(4, 12, "grass-large");
    mRegion->setTile(5, 10, "grass-large");
    mRegion->setTile(5, 12, "grass-large");
    mRegion->setTile(6, 10, "grass-large");
    mRegion->setTile(6, 12, "grass-large");
    mRegion->setTile(7, 12, "grass-large");
    mRegion->setTile(8, 12, "grass-large");
    mRegion->setTile(8, 12, "grass-large");
    mRegion->setTile(9, 12, "grass-large");
    mRegion->setTile(10, 12, "grass-large");
    mRegion->setTile(13, 12, "grass-large");
    mRegion->setTile(14, 12, "grass-large");
    mRegion->setTile(15, 12, "grass-large");
    mRegion->setTile(16, 12, "grass-large");
    mRegion->setTile(17, 12, "grass-large");
    mRegion->setTile(20, 12, "grass-large");
    mRegion->setTile(21, 12, "grass-large");
    mRegion->setTile(22, 12, "grass-large");
    mRegion->setTile(23, 12, "grass-large");
    mRegion->setTile(24, 12, "grass-large");
    mRegion->setTile(27, 12, "grass-large");
    mRegion->setTile(28, 12, "grass-large");
    mRegion->setTile(29, 12, "grass-large");
    mRegion->setTile(30, 12, "grass-large");
    mRegion->setTile(31, 12, "grass-large");
    
    mRegion->setGravity(5.0f);
    
    mDot.reset(new Dot(director(),
                       {100.0f, static_cast<float>(mWindow->size().y / 2)},
                       {0.0f, 0.0f},
                       {0.0f, mRegion->gravity()},
                       {mRegion->width(), mRegion->height()}));
    
    randomGenerator.seed(std::random_device()());
}

void SceneMain::update (float elapsedSeconds)
{
    mDot->update(elapsedSeconds);
    mRegion->update(elapsedSeconds);
    
    mRegion->resolveCollisions(mDot.get());
    
    for (auto & cmdPtr: mCommands)
    {
        cmdPtr->execute();
    }
    mCommands.clear();
    
    frameView();
}

void SceneMain::render ()
{
    mRegion->draw(mWindow.get());
    mDot->draw(mWindow.get());
}

void SceneMain::createTriggers ()
{
    Trigger triggerMoveCharacterLeft {MoveCharacterLeft};
    Trigger triggerMoveCharacterRight {MoveCharacterRight};
    Trigger triggerMoveCharacterUp {MoveCharacterUp};
    Trigger triggerMoveCharacterDown {MoveCharacterDown};
    
    Trigger * triggerPtr = &triggerMoveCharacterLeft;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Left});
    director()->eventManager()->addTrigger(*triggerPtr);
    
    triggerPtr = &triggerMoveCharacterRight;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Right});
    director()->eventManager()->addTrigger(*triggerPtr);
    
    triggerPtr = &triggerMoveCharacterUp;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Up});
    director()->eventManager()->addTrigger(*triggerPtr);
    
    triggerPtr = &triggerMoveCharacterDown;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Down});
    director()->eventManager()->addTrigger(*triggerPtr);
}

void SceneMain::loadTriggers ()
{
    Scene::loadTriggers();
    
    director()->eventManager()->addSubscription(MoveCharacterLeft, name(), shared_from_this());
    director()->eventManager()->addSubscription(MoveCharacterRight, name(), shared_from_this());
    director()->eventManager()->addSubscription(MoveCharacterUp, name(), shared_from_this());
    director()->eventManager()->addSubscription(MoveCharacterDown, name(), shared_from_this());
}

void SceneMain::unloadTriggers ()
{
    Scene::unloadTriggers();
    
    director()->eventManager()->removeSubscription(MoveCharacterLeft, name());
    director()->eventManager()->removeSubscription(MoveCharacterRight, name());
    director()->eventManager()->removeSubscription(MoveCharacterUp, name());
    director()->eventManager()->removeSubscription(MoveCharacterDown, name());
}

void SceneMain::notify (EventParameter eventDetails)
{
    Scene::notify(eventDetails);
    
    if (mActive)
    {
        // Events that we only want to respond to when active.
        if (eventDetails.name() == MoveCharacterLeft ||
            eventDetails.name() == MoveCharacterRight ||
            eventDetails.name() == MoveCharacterUp ||
            eventDetails.name() == MoveCharacterDown)
        {
            sf::Vector2f positionDelta {0.0f, 0.0f};
            
            if (eventDetails.name() == MoveCharacterLeft)
            {
                positionDelta.x -= 7.0f;
            }
            else if (eventDetails.name() == MoveCharacterRight)
            {
                positionDelta.x += 7.0f;
            }
            else if (eventDetails.name() == MoveCharacterUp)
            {
                positionDelta.y -= 225.0f;
            }
            
            mCommands.push_back(unique_ptr<Command>(new MoveDotCommand(mDot, positionDelta)));
        }
    }
    else
    {
        // Events that we only want to respond to when not active.
        if (eventDetails.name() == EventManager::WindowResized)
        {
            frameView();
        }
    }
}
void SceneMain::frameView ()
{
    sf::Vector2f center = mView.getCenter();
    sf::Vector2f size = mView.getSize();
    
    center.x = mDot->position().x;
    if (center.x < size.x / 2)
    {
        center.x = size.x / 2;
    }
    else if (center.x > mRegion->width() - size.x / 2)
    {
        center.x = mRegion->width() - size.x / 2;
    }

    if (size.y < mRegion->height())
    {
        center.y = mRegion->height() - size.y / 2;
    }
    else
    {
        center.y = mRegion->height() / 2;
    }
    
    mView.setCenter(center);
}
