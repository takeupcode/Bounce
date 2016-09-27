//
//  SceneCredits.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/24/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "../EasySFML/Director.h"
#include "../EasySFML/EventManager.h"
#include "../EasySFML/Game.h"
#include "../EasySFML/SceneManager.h"
#include "../EasySFML/Window.h"

#include "OS/Mac/ResourcePath.hpp"
#include "SceneCredits.h"
#include "SceneIdentities.h"

using namespace std;

SceneCredits::SceneCredits (Director * director, int identity, std::shared_ptr<Window> window, bool transparent, bool modal)
: Scene(director, identity, window, transparent, modal)
{
}

void SceneCredits::created ()
{
    Scene::created();
    
    if (hasBeenRecreated())
    {
        return;
    }
    
    mFont.loadFromFile(resourcePath() + "sansation.ttf");
    
    mText.setFont(mFont);
    mText.setString({ "Brought to you by Take Up Code" });
    mText.setCharacterSize(15);
    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
}

void SceneCredits::update (float elapsedSeconds)
{
    mText.setPosition(mWindow->size().x / 2.0f, 100.0f);
}

void SceneCredits::render ()
{
    mWindow->draw(mText);
}

void SceneCredits::loadTriggers ()
{
    Scene::loadTriggers();
    
    director()->eventManager()->addSubscription(EventManager::MenuShow, name(), shared_from_this());
}

void SceneCredits::unloadTriggers ()
{
    Scene::unloadTriggers();
    
    director()->eventManager()->removeSubscription(EventManager::MenuShow, name());
}

void SceneCredits::notify (EventParameter eventDetails)
{
    Scene::notify(eventDetails);
    
    if  (eventDetails.name() == EventManager::MenuShow)
    {
        director()->sceneManager()->addScene(SceneIdentities::MainMenu);
    }
}
