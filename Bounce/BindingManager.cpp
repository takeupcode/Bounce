//
//  BindingManager.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/24/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "BindingManager.h"

using namespace std;

const string BindingManager::WindowClosed = "WindowClosed";
const string BindingManager::WindowResized = "WindowResized";
const string BindingManager::WindowFocusLost = "WindowFocusLost";
const string BindingManager::WindowFocusGained = "WindowFocusGained";
const string BindingManager::WindowToggleFullScreen = "WindowToggleFullScreen";
const string BindingManager::MoveCharacterLeft = "MoveCharacterLeft";
const string BindingManager::MoveCharacterRight = "MoveCharacterRight";
const string BindingManager::MoveCharacterUp = "MoveCharacterUp";
const string BindingManager::MoveCharacterDown = "MoveCharacterDown";

BindingManager::BindingManager ()
: mHasFocus(true)
{ }

bool BindingManager::addBinding (const Binding & binding)
{
    if (mBindings.find(binding.name()) != mBindings.end())
    {
        return false;
    }
    
    return mBindings.emplace(binding.name(), unique_ptr<Binding>(new Binding(binding))).second;
}

bool BindingManager::removeBinding (const std::string & name)
{
    auto position = mBindings.find(name);
    if (position == mBindings.end())
    {
        return false;
    }
    
    mBindings.erase(position);
    
    return true;
}

bool BindingManager::addSubscription (const std::string & bindingName, const std::string & identity,
                                      const std::shared_ptr<EventSubscriber<Binding::BindingEventParameter>> & subscriber)
{
    auto position = mBindings.find(bindingName);
    if (position == mBindings.end())
    {
        return false;
    }
    
    auto event = position->second->eventMatchedEvent();
    event->connect(identity, subscriber);
    
    return true;
}

bool BindingManager::removeSubscription (const std::string & bindingName, const std::string & identity)
{
    auto position = mBindings.find(bindingName);
    if (position == mBindings.end())
    {
        return false;
    }
    
    auto event = position->second->eventMatchedEvent();
    event->disconnect(identity);
    
    return true;
}

void BindingManager::handleEvent (const sf::Event & event)
{
    for (auto & bindingPosition: mBindings)
    {
        bindingPosition.second->handleEvent(event);
    }
}

void BindingManager::handleCurrentStates ()
{
    for (auto & bindingPosition: mBindings)
    {
        bindingPosition.second->handleCurrentStates(mHasFocus);
    }
}

void BindingManager::notify (Binding::BindingEventParameter eventDetails)
{
    if (eventDetails.name() == WindowFocusLost)
    {
        mHasFocus = false;
    }
    else if (eventDetails.name() == WindowFocusGained)
    {
        mHasFocus = true;
    }
}

void BindingManager::loadBindings ()
{
    Binding bindingWindowClosed {WindowClosed};
    Binding bindingWindowResized {WindowResized};
    Binding bindingWindowToggleFullScreen {WindowToggleFullScreen};
    Binding bindingWindowFocusLost {WindowFocusLost};
    Binding bindingWindowFocusGained {WindowFocusGained};
    Binding bindingMoveCharacterLeft {MoveCharacterLeft};
    Binding bindingMoveCharacterRight {MoveCharacterRight};
    Binding bindingMoveCharacterUp {MoveCharacterUp};
    Binding bindingMoveCharacterDown {MoveCharacterDown};
    
    Binding * bindingPtr = &bindingWindowClosed;
    bindingPtr->addBindingPoint(Binding::BindingPoint {Binding::BindingType::WindowClosed, 0, 0, 0});
    addBinding(*bindingPtr);
    
    bindingPtr = &bindingWindowResized;
    bindingPtr->addBindingPoint(Binding::BindingPoint {Binding::BindingType::WindowResized, 0, 0, 0});
    addBinding(*bindingPtr);
    
    bindingPtr = &bindingWindowToggleFullScreen;
    bindingPtr->addBindingPoint(Binding::BindingPoint {Binding::BindingType::KeyboardKeyPressed, 0, 0, sf::Keyboard::Key::F5});
    addBinding(*bindingPtr);
    
    bindingPtr = &bindingWindowFocusLost;
    bindingPtr->addBindingPoint(Binding::BindingPoint {Binding::BindingType::WindowFocusLost, 0, 0, 0});
    addBinding(*bindingPtr);
    
    bindingPtr = &bindingWindowFocusGained;
    bindingPtr->addBindingPoint(Binding::BindingPoint {Binding::BindingType::WindowFocusGained, 0, 0, 0});
    addBinding(*bindingPtr);
    
    bindingPtr = &bindingMoveCharacterLeft;
    bindingPtr->addBindingPoint(Binding::BindingPoint {Binding::BindingType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Left});
    addBinding(*bindingPtr);
    
    bindingPtr = &bindingMoveCharacterRight;
    bindingPtr->addBindingPoint(Binding::BindingPoint {Binding::BindingType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Right});
    addBinding(*bindingPtr);
    
    bindingPtr = &bindingMoveCharacterUp;
    bindingPtr->addBindingPoint(Binding::BindingPoint {Binding::BindingType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Up});
    addBinding(*bindingPtr);
    
    bindingPtr = &bindingMoveCharacterDown;
    bindingPtr->addBindingPoint(Binding::BindingPoint {Binding::BindingType::CurrentKeyboardKeyPressed, 0, 0, sf::Keyboard::Key::Down});
    addBinding(*bindingPtr);
    
    addSubscription(WindowFocusLost, "BindingManager", shared_from_this());
    addSubscription(WindowFocusGained, "BindingManager", shared_from_this());
}
