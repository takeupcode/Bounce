//
//  Scene.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/21/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Director.h"
#include "EventManager.h"
#include "Scene.h"

using namespace std;

Scene::Scene (Director * director, SceneIdentities identity, std::shared_ptr<Window> window, bool transparent, bool modal)
: Directable(director), mIdentity(identity), mWindow(window), mTransparent(transparent), mModal(modal), mActive(false),
mPreviousScene(nullptr), mNextScene(nullptr)
{ }

Scene::~Scene ()
{
}
