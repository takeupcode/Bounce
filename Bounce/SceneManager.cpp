//
//  SceneManager.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Director.h"
#include "Scene.h"
#include "SceneManager.h"

using namespace std;

SceneManager::SceneManager (Director * director)
: Directable(director), mFirstScene(nullptr)
{ }

bool SceneManager::hasScene (SceneIdentities scene)
{
    Scene * currentScene = mFirstScene;
    while (currentScene)
    {
        if (currentScene->identity() == scene)
        {
            for (auto & identity: mScenesToBeRemoved)
            {
                if (identity == scene)
                {
                    return false;
                }
            }
            return true;
        }
        currentScene = currentScene->mNextScene;
    }
    
    return false;
}

bool SceneManager::activateScene (SceneIdentities scene)
{
    for (auto position = mScenesToBeRemoved.begin(); position != mScenesToBeRemoved.end(); ++position)
    {
        if (*position == scene)
        {
            mScenesToBeRemoved.erase(position);
        }
    }
    if (mFirstScene && mFirstScene->identity() != scene)
    {
        mFirstScene->deactivated();
    }
    
    Scene * currentScene = mFirstScene;
    while (currentScene)
    {
        if (currentScene->identity() == scene)
        {
            if (currentScene->mNextScene && currentScene->mPreviousScene)
            {
                currentScene->mNextScene->mPreviousScene = currentScene->mPreviousScene;
                currentScene->mPreviousScene->mNextScene = currentScene->mNextScene;
            }
            else if (currentScene->mPreviousScene)
            {
                currentScene->mPreviousScene->mNextScene = nullptr;
            }
            else
            {
                // The scene is already the most active scene.
                return true;
            }
            
            currentScene->mNextScene = mFirstScene;
            currentScene->mPreviousScene = nullptr;
            
            mFirstScene->mPreviousScene = currentScene;
            mFirstScene = currentScene;
            
            mFirstScene->activated();
            
            return true;
        }
        currentScene = currentScene->mNextScene;
    }
    
    Scene * newScene = mRegisteredScenes[scene].get();
    newScene->mNextScene = mFirstScene;
    newScene->mPreviousScene = nullptr;
    
    if (mFirstScene)
    {
        mFirstScene->mPreviousScene = newScene;
    }
    mFirstScene = newScene;
    
    mFirstScene->created();
    mFirstScene->activated();
    
    return true;
}

bool SceneManager::removeScene (SceneIdentities scene)
{
    if (hasScene(scene))
    {
        mScenesToBeRemoved.push_back(scene);
        return true;
    }
    return false;
}

void SceneManager::processSceneRemovals ()
{
    for (auto & identity: mScenesToBeRemoved)
    {
        Scene * currentScene = mFirstScene;
        while (currentScene)
        {
            if (currentScene->identity() == identity)
            {
                if (currentScene == mFirstScene)
                {
                    currentScene->deactivated();
                }
                
                if (currentScene->mNextScene && currentScene->mPreviousScene)
                {
                    currentScene->mNextScene->mPreviousScene = currentScene->mPreviousScene;
                    currentScene->mPreviousScene->mNextScene = currentScene->mNextScene;
                }
                else if (currentScene->mPreviousScene)
                {
                    currentScene->mPreviousScene->mNextScene = nullptr;
                }
                else
                {
                    currentScene->mNextScene->mPreviousScene = nullptr;
                    
                    mFirstScene = currentScene->mNextScene;
                    
                    mFirstScene->activated();
                }
                
                currentScene->destroyed();
                break;
            }
            currentScene = currentScene->mNextScene;
        }
    }
}

void SceneManager::update (float elapsedSeconds)
{
    Scene * currentScene = mFirstScene;
    if (!currentScene)
    {
        return;
    }
    while (!currentScene->isModal() && currentScene->mNextScene)
    {
        currentScene = currentScene->mNextScene;
    }
    
    while (currentScene)
    {
        currentScene->update(elapsedSeconds);
        currentScene = currentScene->mPreviousScene;
    }
}

void SceneManager::render ()
{
    Scene * currentScene = mFirstScene;
    if (!currentScene)
    {
        return;
    }
    while (currentScene->isTransparent() && currentScene->mNextScene)
    {
        currentScene = currentScene->mNextScene;
    }
    
    while (currentScene)
    {
        currentScene->render();
        currentScene = currentScene->mPreviousScene;
    }
}

void SceneManager::notify (EventParameter eventDetails)
{
    
}

void SceneManager::loadTriggers ()
{
    
}
