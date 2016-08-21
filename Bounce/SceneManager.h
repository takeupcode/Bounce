//
//  SceneManager.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>

#include "Directable.h"
#include "EventDetails.h"
#include "EventSubscriber.h"

class Scene;

class SceneManager : public std::enable_shared_from_this<SceneManager>, public EventSubscriber<EventParameter>,
    public Directable
{
public:
    SceneManager (Director * director);
    
    bool addScene (std::shared_ptr<Scene> scene);
    
    void handleInput ();
    
protected:
    void notify (EventParameter eventDetails) override;
    
private:
    friend class Director;
    
    void loadTriggers ();
    
    std::shared_ptr<Scene> mFirstScene;
};
