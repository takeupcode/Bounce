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

class Window;
class SceneManager;

class Scene : public std::enable_shared_from_this<BounceGame>, public EventSubscriber<EventParameter>,
    public Directable
{
public:
    virtual ~Scene ()
    { }
    
    bool isTransparent ()
    {
        return mTransparent;
    }
    
    bool isModal ()
    {
        return mModal;
    }
    
    virtual void created ()
    { }
    
    virtual void destroyed ()
    { }
    
    virtual void activated ()
    { }
    
    virtual void deactivated ()
    { }
    
    virtual void update (float elapsedSeconds) = 0;
    virtual void render () = 0;
    
protected:
    friend class SceneManager;
    
    Scene (Director * director, std::shared_ptr<Window> window, bool transparent, bool modal)
    : Directable(director), mWindow(window), mTransparent(transparent), mModal(model)
    { }
    
    void notify (EventParameter eventDetails) override
    { }
    
    virtual void loadTriggers () = 0;

private:
    std::shared_ptr<Window> mWindow;
    bool mTransparent;
    bool mModal;
};
