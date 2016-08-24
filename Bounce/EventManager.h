//
//  EventManager.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/24/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Directable.h"
#include "EventDetails.h"
#include "EventSubscriber.h"
#include "Trigger.h"

class Window;

class EventManager : public std::enable_shared_from_this<EventManager>,
    public Directable
{
public:
    static const std::string WindowClosed;
    static const std::string WindowResized;
    static const std::string WindowFocusLost;
    static const std::string WindowFocusGained;
    static const std::string WindowToggleFullScreen;
    static const std::string MoveCharacterLeft;
    static const std::string MoveCharacterRight;
    static const std::string MoveCharacterUp;
    static const std::string MoveCharacterDown;
    static const std::string GamePause;
    static const std::string GameContinue;
    
    explicit EventManager (Director * director);
    
    bool addTrigger (const Trigger & trigger);
    bool removeTrigger (const std::string & name);
    
    bool addSubscription (const std::string & triggerName, const std::string & identity,
                          const std::shared_ptr<EventSubscriber<EventParameter>> & subscriber);
    bool removeSubscription (const std::string & triggerName, const std::string & identity);
    
    void handleEvent (const Window & window, const sf::Event & event);
    void handleCurrentStates (bool hasFocus);
    
private:
    friend class Director;
    
    void createTriggers ();
    void loadTriggers ();
    
    using Triggers = std::unordered_map<std::string, std::unique_ptr<Trigger>>;
    
    Triggers mTriggers;
};
