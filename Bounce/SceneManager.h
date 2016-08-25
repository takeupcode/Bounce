//
//  SceneManager.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <functional>
#include <memory>
#include <map>
#include <vector>

#include "Directable.h"
#include "EventDetails.h"
#include "EventSubscriber.h"
#include "SceneIdentities.h"

class Scene;
class Window;

class SceneManager : public std::enable_shared_from_this<SceneManager>, public EventSubscriber<EventParameter>,
    public Directable
{
public:
    explicit SceneManager (Director * director);
    
    bool hasScene (SceneIdentities scene) const;
    
    SceneIdentities currentScene () const;
    
    bool addScene (SceneIdentities scene, bool addToFront = true);
    
    bool removeScene (SceneIdentities scene);
    
    void processSceneRemovals ();
    
    template <typename T>
    void registerScene (SceneIdentities scene, std::shared_ptr<Window> window, bool transparent, bool modal)
    {
        mRegisteredScenes[scene] = std::shared_ptr<Scene>(static_cast<Scene *>(new T(director(), scene, window, transparent, modal)));
    }
    
    virtual void update (float elapsedSeconds);
    virtual void render ();
    
protected:
    void notify (EventParameter eventDetails) override;
    
private:
    friend class Director;
    
    void loadTriggers ();
    
    Scene * mFirstScene;
    std::map<SceneIdentities, std::shared_ptr<Scene>> mRegisteredScenes;
    std::vector<SceneIdentities> mScenesToBeRemoved;
};
