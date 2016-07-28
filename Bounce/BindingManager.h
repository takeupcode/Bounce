//
//  BindingManager.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/24/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Binding.h"

class BindingManager : public std::enable_shared_from_this<BindingManager>, public EventSubscriber<Binding::BindingEventParameter>
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
    
    BindingManager ();
    
    bool addBinding (const Binding & binding);
    bool removeBinding (const std::string & name);
    
    bool addSubscription (const std::string & bindingName, const std::string & identity,
                          const std::shared_ptr<EventSubscriber<Binding::BindingEventParameter>> & subscriber);
    bool removeSubscription (const std::string & bindingName, const std::string & identity);
    
    void handleEvent (const sf::Event & event);
    void handleCurrentStates ();
    
    void notify (Binding::BindingEventParameter eventDetails) override;
    
    void loadBindings ();

private:
    using Bindings = std::unordered_map<std::string, std::unique_ptr<Binding>>;
    
    Bindings mBindings;
    bool mHasFocus;
};
