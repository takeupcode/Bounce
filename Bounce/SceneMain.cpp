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
    
    mDot.reset(new Dot(director()->textureManager()->texture(sphere), sf::Vector2f(mWindow->size().x / 2, mWindow->size().y / 2), sf::Vector2u(mWindow->size().x, mWindow->size().y)));

    mTileSheet.reset(new SpriteSheet(director()->textureManager()->texture(tiles)));
    AnimationDefinition * animation = mTileSheet->addAnimation("grass-large", "");
    animation->addFrame(1.0f, {0, 0}, {48, 48});
    
    mRegion.reset(new Region(mTileSheet, {1.0f, 1.0f}, {16, 16}, 48, 40));
    mRegion->addTileType("grass-large", "grass-large");
    mRegion->setTile(0, 0, "grass-large");
    mRegion->setTile(45, 0, "grass-large");
    mRegion->setTile(0, 31, "grass-large");
    mRegion->setTile(0, 34, "grass-large");
    mRegion->setTile(0, 37, "grass-large");
    mRegion->setTile(3, 34, "grass-large");
    mRegion->setTile(3, 37, "grass-large");
    mRegion->setTile(6, 37, "grass-large");
    mRegion->setTile(9, 37, "grass-large");
    mRegion->setTile(12, 37, "grass-large");
    mRegion->setTile(15, 37, "grass-large");
    mRegion->setTile(18, 37, "grass-large");
    mRegion->setTile(21, 37, "grass-large");
    mRegion->setTile(24, 37, "grass-large");
    mRegion->setTile(27, 37, "grass-large");
    mRegion->setTile(30, 37, "grass-large");
    mRegion->setTile(39, 37, "grass-large");
    mRegion->setTile(42, 37, "grass-large");
    mRegion->setTile(45, 37, "grass-large");
    
    mRegion->setGravity(5.0f);
    
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
    for (auto & cmdPtr: mCommands)
    {
        cmdPtr->execute();
    }
    if (mCommands.empty())
    {
        mDot->move({0.0f, mRegion->gravity()}, elapsedSeconds);
    }
    else
    {
        mCommands.clear();
    }
    
    mRegion->update(elapsedSeconds);
    
    mRegion->resolveCollisions(mDot.get());
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
            positionDelta.x -= 10.0f;
        }
        else if (eventDetails.name() == MoveCharacterRight)
        {
            positionDelta.x += 10.0f;
        }
        else if (eventDetails.name() == MoveCharacterUp)
        {
            positionDelta.y -= 200.0f;
        }
        
        float elapsedSeconds = director()->game()->elapsed().asSeconds();
        mCommands.push_back(unique_ptr<Command>(new MoveDotCommand(mDot, positionDelta, elapsedSeconds)));
    }
}
