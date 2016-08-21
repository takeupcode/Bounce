//
//  SceneManager.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "SceneManager.h"

using namespace std;

SceneManager::SceneManager (Director * director)
: Directable(director)
{ }

bool SceneManager::addScene (std::shared_ptr<Scene> scene)
{
    return true;
}

void SceneManager::handleInput ()
{
    
}

void SceneManager::notify (EventParameter eventDetails)
{
    
}

void SceneManager::loadTriggers ()
{
    
}
