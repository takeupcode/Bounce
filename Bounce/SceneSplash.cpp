//
//  SceneSplash.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Director.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "SceneSplash.h"
#include "Window.h"

#include "ResourcePath.hpp"

SceneSplash::SceneSplash (Director * director, SceneIdentities identity, std::shared_ptr<Window> window, bool transparent, bool modal)
: Scene(director, identity, window, transparent, modal)
{
    
}

void SceneSplash::created ()
{
    if (hasBeenCreated())
    {
        return;
    }
    Scene::created();
    
    mTimePassed = 0.0f;
    
    mFont.loadFromFile(resourcePath() + "sansation.ttf");
    
    mText.setFont(mFont);
    mText.setString({ "Press any key to begin." });
    mText.setCharacterSize(15);
    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    mText.setPosition(mWindow->size().x / 2.0f, mWindow->size().y / 2.0f);
}

void SceneSplash::update (float elapsedSeconds)
{
    mTimePassed += elapsedSeconds;
}

void SceneSplash::render ()
{
    mWindow->drawBegin();

    if (mTimePassed > 5.0f)
    {
        mWindow->draw(mText);
    }
    
    mWindow->drawEnd();
}

void SceneSplash::loadTriggers ()
{
    director()->eventManager()->addSubscription(EventManager::GameContinue, "SceneSplash", shared_from_this());
}

void SceneSplash::unloadTriggers ()
{
    director()->eventManager()->removeSubscription(EventManager::GameContinue, "SceneSplash");
}

void SceneSplash::notify (EventParameter eventDetails)
{
    if  (eventDetails.name() == EventManager::GameContinue)
    {
        director()->sceneManager()->activateScene(SceneIdentities::MainMenu);
    }
}
