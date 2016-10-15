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
#include "HeroCommand.h"
#include "SceneIdentities.h"
#include "SceneMain.h"
#include "WindowIdentities.h"

#include "OS/Mac/ResourcePath.hpp"

using namespace std;

const string SceneMain::CharacterWalkLeft = "CharacterWalkLeft";
const string SceneMain::CharacterWalkRight = "CharacterWalkRight";
const string SceneMain::CharacterRunLeft = "CharacterRunLeft";
const string SceneMain::CharacterRunRight = "CharacterRunRight";
const string SceneMain::CharacterJump = "CharacterJump";

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
    director()->textureManager()->loadTexture(tiles, resourcePath() + "Tiles.png");

    mTileSheet.reset(new SpriteSheet(tiles, resourcePath() + "Tiles.json", director()->textureManager()->texture(tiles)));
    AnimationDefinition * animation = mTileSheet->addAnimation("grass-large", "");
    FrameDefinition * frame = animation->addFrame("Large/Grass", 1.0f);
    frame->addTag("friction", -5.0f);
    
    mRegion.reset(new Region(mTileSheet, {1.5f, 1.5f}, {48, 48}, 32, 13));
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
    
    mHero.reset(new Hero(director(),
                       {100.0f, static_cast<float>(mWindow->size().y / 2)},
                       {0.0f, 0.0f},
                       {0.0f, mRegion->gravity()},
                       {mRegion->width(), mRegion->height()}));
    
    randomGenerator.seed(std::random_device()());
}

void SceneMain::update (float elapsedSeconds)
{
    mHero->update(elapsedSeconds);
    mRegion->update(elapsedSeconds);
    
    mRegion->resolveCollisions(mHero.get());
    
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
    mHero->draw(mWindow.get());
}

void SceneMain::createTriggers ()
{
    Trigger triggerCharacterWalkLeft {CharacterWalkLeft};
    Trigger triggerCharacterWalkRight {CharacterWalkRight};
    Trigger triggerCharacterRunLeft {CharacterRunLeft};
    Trigger triggerCharacterRunRight {CharacterRunRight};
    Trigger triggerCharacterJump {CharacterJump};
    
    Trigger * triggerPtr = &triggerCharacterWalkLeft;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Left});
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyNotPressed, 0, 0, sf::Keyboard::Key::Right});
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyNotPressed, 0, 0, sf::Keyboard::Key::LShift});
    director()->eventManager()->addTrigger(*triggerPtr);
    
    triggerPtr = &triggerCharacterWalkRight;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Right});
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyNotPressed, 0, 0, sf::Keyboard::Key::Left});
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyNotPressed, 0, 0, sf::Keyboard::Key::LShift});
    director()->eventManager()->addTrigger(*triggerPtr);
    
    triggerPtr = &triggerCharacterRunLeft;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Left});
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyNotPressed, 0, 0, sf::Keyboard::Key::Right});
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::LShift});
    director()->eventManager()->addTrigger(*triggerPtr);
    
    triggerPtr = &triggerCharacterRunRight;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Right});
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyNotPressed, 0, 0, sf::Keyboard::Key::Left});
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::LShift});
    director()->eventManager()->addTrigger(*triggerPtr);
    
    triggerPtr = &triggerCharacterJump;
    triggerPtr->addTriggerPoint(Trigger::TriggerPoint {Trigger::TriggerType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Up});
    director()->eventManager()->addTrigger(*triggerPtr);
}

void SceneMain::loadTriggers ()
{
    Scene::loadTriggers();
    
    director()->eventManager()->addSubscription(CharacterWalkLeft, name(), shared_from_this());
    director()->eventManager()->addSubscription(CharacterWalkRight, name(), shared_from_this());
    director()->eventManager()->addSubscription(CharacterRunLeft, name(), shared_from_this());
    director()->eventManager()->addSubscription(CharacterRunRight, name(), shared_from_this());
    director()->eventManager()->addSubscription(CharacterJump, name(), shared_from_this());
}

void SceneMain::unloadTriggers ()
{
    Scene::unloadTriggers();
    
    director()->eventManager()->removeSubscription(CharacterWalkLeft, name());
    director()->eventManager()->removeSubscription(CharacterWalkRight, name());
    director()->eventManager()->removeSubscription(CharacterRunLeft, name());
    director()->eventManager()->removeSubscription(CharacterRunRight, name());
    director()->eventManager()->removeSubscription(CharacterJump, name());
}

void SceneMain::notify (EventParameter eventDetails)
{
    Scene::notify(eventDetails);
    
    if (mActive)
    {
        // Events that we only want to respond to when active.
        if (eventDetails.name() == CharacterWalkLeft)
        {
            mCommands.push_back(unique_ptr<Command>(new HeroCommand(mHero, Hero::CommandWalkWest)));
        }
        else if (eventDetails.name() == CharacterWalkRight)
        {
            mCommands.push_back(unique_ptr<Command>(new HeroCommand(mHero, Hero::CommandWalkEast)));
        }
        else if (eventDetails.name() == CharacterRunLeft)
        {
            mCommands.push_back(unique_ptr<Command>(new HeroCommand(mHero, Hero::CommandRunWest)));
        }
        else if (eventDetails.name() == CharacterRunRight)
        {
            mCommands.push_back(unique_ptr<Command>(new HeroCommand(mHero, Hero::CommandRunEast)));
        }
        else if (eventDetails.name() == CharacterJump)
        {
            mCommands.push_back(unique_ptr<Command>(new HeroCommand(mHero, Hero::CommandJump)));
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
    
    center.x = mHero->position().x;
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
