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
    director()->textureManager()->loadTexture(sphere, resourcePath() + "sphere.png");
    
    mDot.reset(new Dot(director()->textureManager()->texture(sphere), sf::Vector2f(mWindow->size().x / 2, mWindow->size().y / 2), sf::Vector2u(mWindow->size().x, mWindow->size().y)));
    
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
    sf::Vector2f positionDelta {0.0f, 0.0f};
    positionDelta.x += uniformDistribution(randomGenerator);
    positionDelta.y += uniformDistribution(randomGenerator);
    
    mCommands.push_back(unique_ptr<Command>(new MoveDotCommand(mDot, positionDelta, elapsedSeconds)));
    
    for (auto & cmdPtr: mCommands)
    {
        cmdPtr->execute();
    }
    mCommands.clear();
}

void SceneMain::render ()
{
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
            positionDelta.y -= 10.0f;
        }
        else if (eventDetails.name() == MoveCharacterDown)
        {
            positionDelta.y += 10.0f;
        }
        
        float elapsedSeconds = director()->game()->elapsed().asSeconds();
        mCommands.push_back(unique_ptr<Command>(new MoveDotCommand(mDot, positionDelta, elapsedSeconds)));
    }
}
