//
//  SceneSplash.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "../EasySFML/Director.h"
#include "../EasySFML/EventManager.h"
#include "../EasySFML/SceneManager.h"
#include "../EasySFML/Window.h"

#include "SceneIdentities.h"
#include "SceneSplash.h"

#include "ResourcePath.hpp"

SceneSplash::SceneSplash (Director * director, int identity, std::shared_ptr<Window> window, bool transparent, bool modal)
: Scene(director, identity, window, transparent, modal)
{
    
}

void SceneSplash::created ()
{
    Scene::created();
    
    if (hasBeenRecreated())
    {
        return;
    }
    
    mTimePassed = 0.0f;
    
    mFont.loadFromFile(resourcePath() + "sansation.ttf");
    
    mText.setFont(mFont);
    mText.setString({ "Press any key to begin." });
    mText.setCharacterSize(15);
    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
}

void SceneSplash::update (float elapsedSeconds)
{
    mTimePassed += elapsedSeconds;
    
    mText.setPosition(mWindow->size().x / 2.0f, mWindow->size().y / 2.0f);
}

void SceneSplash::render ()
{
    if (mTimePassed > 5.0f)
    {
        mWindow->draw(mText);
    }
}

void SceneSplash::loadTriggers ()
{
    Scene::loadTriggers();
    
    director()->eventManager()->addSubscription(EventManager::GameContinue, name(), shared_from_this());
}

void SceneSplash::unloadTriggers ()
{
    Scene::unloadTriggers();
    
    director()->eventManager()->removeSubscription(EventManager::GameContinue, name());
}

void SceneSplash::notify (EventParameter eventDetails)
{
    Scene::notify(eventDetails);
    
    if  (eventDetails.name() == EventManager::GameContinue)
    {
        director()->sceneManager()->removeScene(SceneIdentities::Splash);
        director()->sceneManager()->addScene(SceneIdentities::MainMenu);
    }
}
