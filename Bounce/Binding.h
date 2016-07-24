//
//  Binding.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "EventPublisher.h"

class Binding
{
    enum class BindingType
    {
        // These types map to event types.
        WindowClosed = sf::Event::Closed,
        WindowResized = sf::Event::Resized,
        WindowLostFocus = sf::Event::LostFocus,
        WindowGainedFocus = sf::Event::GainedFocus,
        KeyboardTextEntered = sf::Event::TextEntered,
        KeyboardKeyPressed = sf::Event::KeyPressed,
        KeyboardKeyReleased = sf::Event::KeyReleased,
        MouseWheelScrolled = sf::Event::MouseWheelScrolled,
        MouseButtonPressed = sf::Event::MouseButtonPressed,
        MouseButtonReleased = sf::Event::MouseButtonReleased,
        MouseMoved = sf::Event::MouseMoved,
        MouseEntered = sf::Event::MouseEntered,
        MouseDeparted = sf::Event::MouseLeft,
        JoystickButtonPressed = sf::Event::JoystickButtonPressed,
        JoystickButtonReleased = sf::Event::JoystickButtonReleased,
        JoystickMoved = sf::Event::JoystickMoved,
        JoystickConnected = sf::Event::JoystickConnected,
        JoystickDisconnected = sf::Event::JoystickDisconnected,
        TouchBegan = sf::Event::TouchBegan,
        TouchMoved = sf::Event::TouchMoved,
        TouchEnded = sf::Event::TouchEnded,
        SensorChanged = sf::Event::SensorChanged,
        
        // And these types represent current states.
        CurrentKeyboardKeyPressed = sf::Event::Count + 1,
        CurrentMouseButtonPressed,
        CurrentGamepadButtonPressed
    };

    class BindingPoint
    {
    public:
        explicit BindingPoint (BindingType type, unsigned long code = 0)
        : mType(type), mCode(code)
        { }
        
        BindingType type ()
        {
            return mType;
        }
        
        unsigned long code ()
        {
            return mCode;
        }
        
        bool isEventType ()
        {
            return static_cast<unsigned int>(mType) < static_cast<unsigned int>(sf::Event::Count);
        }

    private:
        BindingType mType;
        unsigned long mCode;
    };
    
    class EventDetails
    {
    public:
        EventDetails (const std::string & name)
        : mName(name)
        {
            clear();
        }
        
        std::string name ()
        {
            return mName;
        }
        
        bool hasSize ()
        {
            return mHasSize;
        }
        
        sf::Event::SizeEvent size ()
        {
            return mSize;
        }
        
        void setSize (const sf::Event::SizeEvent & event)
        {
            mSize = event;
            mHasSize = true;
        }
        
        bool hasKey ()
        {
            return mHasKey;
        }
        
        sf::Event::KeyEvent key ()
        {
            return mKey;
        }
        
        void setKey (const sf::Event::KeyEvent & event)
        {
            mKey = event;
            mHasKey = true;
        }
        
        bool hasText ()
        {
            return mHasText;
        }
        
        sf::Event::TextEvent text ()
        {
            return mText;
        }
        
        void setText (const sf::Event::TextEvent & event)
        {
            mText = event;
            mHasText = true;
        }
        
        bool hasMouseMove ()
        {
            return mHasMouseMove;
        }
        
        sf::Event::MouseMoveEvent mouseMove ()
        {
            return mMouseMove;
        }
        
        void setMouseMove (const sf::Event::MouseMoveEvent & event)
        {
            mMouseMove = event;
            mHasMouseMove = true;
        }
        
        bool hasMouseButton ()
        {
            return mHasMouseButton;
        }
        
        sf::Event::MouseButtonEvent mouseButton ()
        {
            return mMouseButton;
        }
        
        void setMouseButton (const sf::Event::MouseButtonEvent & event)
        {
            mMouseButton = event;
            mHasMouseButton = true;
        }
        
        bool hasMouseWheel ()
        {
            return mHasMouseWheel;
        }
        
        sf::Event::MouseWheelScrollEvent mouseWheel ()
        {
            return mMouseWheel;
        }
        
        void setMouseWheel (const sf::Event::MouseWheelScrollEvent & event)
        {
            mMouseWheel = event;
            mHasMouseWheel = true;
        }
        
        bool hasJoystickMove ()
        {
            return mHasJoystickMove;
        }
        
        sf::Event::JoystickMoveEvent joystickMove ()
        {
            return mJoystickMove;
        }
        
        void setJoystickMove (const sf::Event::JoystickMoveEvent & event)
        {
            mJoystickMove = event;
            mHasJoystickMove = true;
        }
        
        bool hasJoystickButton ()
        {
            return mHasJoystickButton;
        }
        
        sf::Event::JoystickButtonEvent joystickButton ()
        {
            return mJoystickButton;
        }
        
        void setJoystickButton (const sf::Event::JoystickButtonEvent & event)
        {
            mJoystickButton = event;
            mHasJoystickButton = true;
        }
        
        bool hasJoystickConnect ()
        {
            return mHasJoystickConnect;
        }
        
        sf::Event::JoystickConnectEvent joystickConnect ()
        {
            return mJoystickConnect;
        }
        
        void setJoystickConnect (const sf::Event::JoystickConnectEvent & event)
        {
            mJoystickConnect = event;
            mHasJoystickConnect = true;
        }
        
        bool hasTouch ()
        {
            return mHasTouch;
        }
        
        sf::Event::TouchEvent touch ()
        {
            return mTouch;
        }
        
        void setTouch (const sf::Event::TouchEvent & event)
        {
            mTouch = event;
            mHasTouch = true;
        }
        
        bool hasSensor ()
        {
            return mHasSensor;
        }
        
        sf::Event::SensorEvent sensor ()
        {
            return mSensor;
        }
        
        void setSensor (const sf::Event::SensorEvent & event)
        {
            mSensor = event;
            mHasSensor = true;
        }
        
        void clear ()
        {
            mHasSize = false;
            mHasKey = false;
            mHasText = false;
            mHasMouseMove = false;
            mHasMouseButton = false;
            mHasMouseWheel = false;
            mHasJoystickMove = false;
            mHasJoystickButton = false;
            mHasJoystickConnect = false;
            mHasTouch = false;
            mHasSensor = false;
        }
        
    private:
        std::string mName;
        bool mHasSize;
        bool mHasKey;
        bool mHasText;
        bool mHasMouseMove;
        bool mHasMouseButton;
        bool mHasMouseWheel;
        bool mHasJoystickMove;
        bool mHasJoystickButton;
        bool mHasJoystickConnect;
        bool mHasTouch;
        bool mHasSensor;
        sf::Event::SizeEvent mSize;
        sf::Event::KeyEvent mKey;
        sf::Event::TextEvent mText;
        sf::Event::MouseMoveEvent mMouseMove;
        sf::Event::MouseButtonEvent mMouseButton;
        sf::Event::MouseWheelScrollEvent mMouseWheel;
        sf::Event::JoystickMoveEvent mJoystickMove;
        sf::Event::JoystickButtonEvent mJoystickButton;
        sf::Event::JoystickConnectEvent mJoystickConnect;
        sf::Event::TouchEvent mTouch;
        sf::Event::SensorEvent mSensor;
    };
    
    using BindingPoints = std::vector<BindingPoint>;
    using BindingEvent = EventPublisher<const EventDetails &>;

    Binding (const std::string & name)
    : mName(name), mDetails(name), mBindingPointMatches(0), mEventMatched(new BindingEvent())
    { }
    
    void addBindingPoint (const BindingPoint & bindingPoint)
    {
        mBindingPoints.push_back(bindingPoint);
    }
    
    BindingEvent * eventMatched ()
    {
        return mEventMatched.get();
    }

private:
    std::string mName;
    EventDetails mDetails;
    BindingPoints mBindingPoints;
    unsigned int mBindingPointMatches;
    std::unique_ptr<BindingEvent> mEventMatched;
};
