//
//  SceneMainMenu.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "../EasySFML/Director.h"
#include "../EasySFML/EventManager.h"
#include "../EasySFML/Game.h"
#include "../EasySFML/SceneManager.h"
#include "../EasySFML/Window.h"

#include "SceneIdentities.h"
#include "SceneMainMenu.h"

#include "OS/Mac/ResourcePath.hpp"

using namespace std;

SceneMainMenu::SceneMainMenu (Director * director, int identity, std::shared_ptr<Window> window, bool transparent, bool modal)
: Scene(director, identity, window, transparent, modal)
{
    
}

void SceneMainMenu::created ()
{
    Scene::created();
    
    if (hasBeenRecreated())
    {
        return;
    }
    
    mFont.loadFromFile(resourcePath() + "sansation.ttf");
    
    mMenuTitle.setFont(mFont);
    mMenuTitle.setString({ "Main Menu" });
    mMenuTitle.setCharacterSize(20);
    sf::FloatRect textRect = mMenuTitle.getLocalBounds();
    mMenuTitle.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
    
    mButtonPadding = 5;
    
    string labels[3] =
    {
    "Play",
    "Credits",
    "Quit"
    };
    
    for (int i = 0; i < 3; ++i)
    {
        mButtons[i].setFillColor(sf::Color::Red);
        
        mButtonText[i].setFont(mFont);
        mButtonText[i].setString(sf::String(labels[i]));
        mButtonText[i].setCharacterSize(12);
        
        sf::FloatRect rect = mButtonText[i].getLocalBounds();
        mButtonText[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    }
}

void SceneMainMenu::activated ()
{
    Scene::activated();
    
    string label = director()->sceneManager()->hasScene(SceneIdentities::Level01) ? "Resume" : "Play";
    
    mButtonText[0].setString(sf::String(label));
    
    sf::FloatRect rect = mButtonText[0].getLocalBounds();
    mButtonText[0].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
}

void SceneMainMenu::update (float elapsedSeconds)
{
    mMenuTitle.setPosition(mWindow->size().x / 2.0f, 100.0f);
    
    mButtonSize = sf::Vector2f(mWindow->size().x - 100.0f, 32.0f);
    mButtonPosition = sf::Vector2f(mWindow->size().x / 2.0f, 200);
    
    for (int i = 0; i < 3; ++i)
    {
        sf::Vector2f buttonPosition(mButtonPosition.x, mButtonPosition.y + (i * (mButtonSize.y + mButtonPadding)));
        
        mButtons[i].setSize(mButtonSize);
        mButtons[i].setOrigin(mButtonSize.x / 2.0f, mButtonSize.y / 2.0f);
        mButtons[i].setPosition(buttonPosition);
        
        mButtonText[i].setPosition(buttonPosition);
    }
}

void SceneMainMenu::render ()
{
    mWindow->draw(mMenuTitle);
    
    for (int i = 0; i < 3; ++i)
    {
        mWindow->draw(mButtons[i]);
        mWindow->draw(mButtonText[i]);
    }
}

void SceneMainMenu::loadTriggers ()
{
    Scene::loadTriggers();
    
    director()->eventManager()->addSubscription(EventManager::MenuSelect, name(), shared_from_this());
    director()->eventManager()->addSubscription(EventManager::MenuShow, name(), shared_from_this());
}

void SceneMainMenu::unloadTriggers ()
{
    Scene::unloadTriggers();
    
    director()->eventManager()->removeSubscription(EventManager::MenuSelect, name());
    director()->eventManager()->removeSubscription(EventManager::MenuShow, name());
}

void SceneMainMenu::notify (EventParameter eventDetails)
{
    Scene::notify(eventDetails);
    
    if  (eventDetails.name() == EventManager::MenuSelect)
    {
        if (mActive)
        {
            sf::Vector2i mousePosition = {eventDetails.mouseButton().x, eventDetails.mouseButton().y};
            
            float halfWidth = mButtonSize.x / 2.0f;
            float halfHeight = mButtonSize.y / 2.0f;
            
            for (int i = 0; i < 3; ++i)
            {
                if(mousePosition.x >= mButtons[i].getPosition().x - halfWidth &&
                   mousePosition.x <= mButtons[i].getPosition().x + halfWidth &&
                   mousePosition.y >= mButtons[i].getPosition().y - halfHeight &&
                   mousePosition.y <= mButtons[i].getPosition().y + halfHeight)
                {
                    switch (i)
                    {
                    case 0:
                        director()->sceneManager()->addScene(SceneIdentities::Level01);
                        break;
                            
                    case 1:
                        director()->sceneManager()->addScene(SceneIdentities::Credits);
                        break;
                        
                    case 2:
                        director()->game()->quit();
                        break;
                    }
                }
            }
        }
    }
    else if  (eventDetails.name() == EventManager::MenuShow)
    {
        int currentSceneIdentity = director()->sceneManager()->currentScene();
        if (currentSceneIdentity != SceneIdentities::Paused)
        {
            director()->sceneManager()->addScene(SceneIdentities::MainMenu);
        }
    }
}
