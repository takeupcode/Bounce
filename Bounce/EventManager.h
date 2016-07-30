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

#include "Trigger.h"

class EventManager : public std::enable_shared_from_this<EventManager>, public EventSubscriber<Trigger::EventParameter>
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
    
    EventManager ();
    
    bool addTrigger (const Trigger & trigger);
    bool removeTrigger (const std::string & name);
    
    bool addSubscription (const std::string & triggerName, const std::string & identity,
                          const std::shared_ptr<EventSubscriber<Trigger::EventParameter>> & subscriber);
    bool removeSubscription (const std::string & triggerName, const std::string & identity);
    
    void handleEvent (const sf::Event & event);
    void handleCurrentStates ();
    
    void notify (Trigger::EventParameter eventDetails) override;
    
    void loadTriggers ();

private:
    using Triggers = std::unordered_map<std::string, std::unique_ptr<Trigger>>;
    
    Triggers mTriggers;
    bool mHasFocus;
};
