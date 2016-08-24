//
//  Scene.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/31/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>

#include "Directable.h"
#include "EventDetails.h"
#include "EventSubscriber.h"
#include "SceneIdentities.h"

class Window;
class SceneManager;

class Scene : public std::enable_shared_from_this<Scene>, public EventSubscriber<EventParameter>,
    public Directable
{
public:
    virtual ~Scene ();

    SceneIdentities identity () const
    {
        return mIdentity;
    }

    bool isTransparent () const
    {
        return mTransparent;
    }
    
    bool isModal () const
    {
        return mModal;
    }
    
    bool isActive () const
    {
        return mActive;
    }
    
    virtual void created ()
    {
        mCreated = true;
    }
    
    virtual void destroyed ()
    {
    }
    
    virtual void activated ()
    {
        loadTriggers();
        
        mActive = true;
    }
    
    virtual void deactivated ()
    {
        unloadTriggers();
        
        mActive = false;
    }
    
    bool hasBeenCreated ()
    {
        return mCreated;
    }
    
    virtual void update (float elapsedSeconds) = 0;
    virtual void render () = 0;
    
protected:
    friend class SceneManager;
    
    Scene (Director * director, SceneIdentities identity, std::shared_ptr<Window> window, bool transparent, bool modal);
    
    virtual void loadTriggers () = 0;
    virtual void unloadTriggers () = 0;
    
    void notify (EventParameter eventDetails) override
    { }
    
    std::shared_ptr<Window> mWindow;

private:
    SceneIdentities mIdentity;
    bool mTransparent;
    bool mModal;
    bool mActive;
    Scene * mPreviousScene;
    Scene * mNextScene;
    bool mCreated;
};
