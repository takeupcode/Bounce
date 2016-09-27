//
//  ScenePaused.cpp
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

#include "SceneIdentities.h"
#include "ScenePaused.h"

#include "OS/Mac/ResourcePath.hpp"

using namespace std;

ScenePaused::ScenePaused (Director * director, int identity, std::shared_ptr<Window> window, bool transparent, bool modal)
: Scene(director, identity, window, transparent, modal)
{
}

void ScenePaused::created ()
{
    Scene::created();
    
    if (hasBeenRecreated())
    {
        return;
    }
    
    mFont.loadFromFile(resourcePath() + "sansation.ttf");
    
    mText.setFont(mFont);
    mText.setString({ "Paused" });
    mText.setCharacterSize(15);
    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width / 2.0f,
                         textRect.top + textRect.height / 2.0f);
}

void ScenePaused::update (float elapsedSeconds)
{
    mText.setPosition(mWindow->size().x / 2.0f, 100.0f);
}

void ScenePaused::render ()
{
    mWindow->draw(mText);
}

void ScenePaused::loadTriggers ()
{
    Scene::loadTriggers();
    
    director()->eventManager()->addSubscription(EventManager::GamePause, name(), shared_from_this());
}

void ScenePaused::unloadTriggers ()
{
    Scene::unloadTriggers();
    
    director()->eventManager()->removeSubscription(EventManager::GamePause, name());
}

void ScenePaused::notify (EventParameter eventDetails)
{
    Scene::notify(eventDetails);
    
    if  (eventDetails.name() == EventManager::GamePause)
    {
        int currentSceneIdentity = director()->sceneManager()->currentScene();
        if (currentSceneIdentity == SceneIdentities::Paused)
        {
            director()->sceneManager()->addScene(SceneIdentities::Level01);
        }
        else if (currentSceneIdentity != SceneIdentities::Splash &&
                 currentSceneIdentity != SceneIdentities::MainMenu &&
                 currentSceneIdentity != SceneIdentities::GameOver &&
                 currentSceneIdentity != SceneIdentities::Credits)
        {
            director()->sceneManager()->addScene(SceneIdentities::Paused);
        }
    }
}
