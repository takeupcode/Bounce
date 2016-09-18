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
    if (hasBeenCreated())
    {
        return;
    }
    Scene::created();
    
    string sphere = "sphere";
    string tiles = "tiles";
    director()->textureManager()->loadTexture(sphere, resourcePath() + "hero.png");
    director()->textureManager()->loadTexture(tiles, resourcePath() + "tiles.png");

    mTileSheet.reset(new SpriteSheet(director()->textureManager()->texture(tiles)));
    AnimationDefinition * animation = mTileSheet->addAnimation("grass-large", "");
    animation->addFrame(1.0f, {0, 0}, {48, 48});
    
    mRegion.reset(new Region(mTileSheet, {1.0f, 1.0f}, {48, 48}, 16, 13));
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
    mRegion->setTile(5, 12, "grass-large");
    mRegion->setTile(6, 12, "grass-large");
    mRegion->setTile(7, 12, "grass-large");
    mRegion->setTile(8, 12, "grass-large");
    mRegion->setTile(8, 12, "grass-large");
    mRegion->setTile(9, 12, "grass-large");
    mRegion->setTile(10, 12, "grass-large");
    mRegion->setTile(13, 12, "grass-large");
    mRegion->setTile(14, 12, "grass-large");
    mRegion->setTile(15, 12, "grass-large");
    
    mRegion->setGravity(5.0f);
    
    mDot.reset(new Dot(director()->textureManager()->texture(sphere),
                       {static_cast<float>(mWindow->size().x / 2), static_cast<float>(mWindow->size().y / 2)},
                       {0.0f, 0.0f},
                       {0.0f, mRegion->gravity()},
                       {mWindow->size().x, mWindow->size().y}));
    
    randomGenerator.seed(std::random_device()());
    
    Trigger triggerMoveCharacterLeft {MoveCharacterLeft};
    Trigger triggerMoveCharacterRight {MoveCharacterRight};
    Trigger triggerMoveCharacterUp {MoveCharacterUp};
    Trigger triggerMoveCharacterDown {MoveCharacterDown};
    
    Trigger * triggerPtr = &triggerMoveCharacterLeft;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::KeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Left});
    director()->eventManager()->addTrigger(*triggerPtr);
    
    triggerPtr = &triggerMoveCharacterRight;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::KeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Right});
    director()->eventManager()->addTrigger(*triggerPtr);
    
    triggerPtr = &triggerMoveCharacterUp;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::KeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Up});
    director()->eventManager()->addTrigger(*triggerPtr);
    
    triggerPtr = &triggerMoveCharacterDown;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::KeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Down});
    director()->eventManager()->addTrigger(*triggerPtr);
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
}

void SceneMain::render ()
{
    mRegion->draw(mWindow.get());
    mDot->draw(mWindow.get());
}

void SceneMain::loadTriggers ()
{
    director()->eventManager()->addSubscription(MoveCharacterLeft, "SceneMain", shared_from_this());
    director()->eventManager()->addSubscription(MoveCharacterRight, "SceneMain", shared_from_this());
    director()->eventManager()->addSubscription(MoveCharacterUp, "SceneMain", shared_from_this());
    director()->eventManager()->addSubscription(MoveCharacterDown, "SceneMain", shared_from_this());
}

void SceneMain::unloadTriggers ()
{
    director()->eventManager()->removeSubscription(MoveCharacterLeft, "SceneMain");
    director()->eventManager()->removeSubscription(MoveCharacterRight, "SceneMain");
    director()->eventManager()->removeSubscription(MoveCharacterUp, "SceneMain");
    director()->eventManager()->removeSubscription(MoveCharacterDown, "SceneMain");
}

void SceneMain::notify (EventParameter eventDetails)
{
    if (eventDetails.name() == MoveCharacterLeft ||
        eventDetails.name() == MoveCharacterRight ||
        eventDetails.name() == MoveCharacterUp ||
        eventDetails.name() == MoveCharacterDown)
    {
        sf::Vector2f positionDelta {0.0f, 0.0f};
        
        if (eventDetails.name() == MoveCharacterLeft)
        {
            positionDelta.x -= 30.0f;
        }
        else if (eventDetails.name() == MoveCharacterRight)
        {
            positionDelta.x += 30.0f;
        }
        else if (eventDetails.name() == MoveCharacterUp)
        {
            positionDelta.y -= 250.0f;
        }
        
        mCommands.push_back(unique_ptr<Command>(new MoveDotCommand(mDot, positionDelta)));
    }
}
