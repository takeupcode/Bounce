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
public:
    enum class BindingType
    {
        // These types map to event types.
        WindowClosed = sf::Event::Closed,
        WindowResized = sf::Event::Resized,
        WindowFocusLost = sf::Event::LostFocus,
        WindowFocusGained = sf::Event::GainedFocus,
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
        CurrentJoystickButtonPressed
    };

    class BindingPoint
    {
    public:
        explicit BindingPoint (BindingType type, int device = 0, int axis = 0, int code = 0)
        : mData(new BindingPointData(type, device, axis, code))
        { }
        
        BindingPoint (const BindingPoint & src)
        : mData(new BindingPointData(*src.mData))
        { }
        
        BindingPoint (BindingPoint && src)
        : mData(src.mData.release())
        { }
        
        ~BindingPoint ()
        { }
        
        void swap (BindingPoint & other)
        {
            std::unique_ptr<BindingPointData> thisData(mData.release());
            std::unique_ptr<BindingPointData> otherData(other.mData.release());
            
            mData.reset(otherData.release());
            other.mData.reset(thisData.release());
        }
        
        BindingPoint & operator = (const BindingPoint & rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            
            *mData = *rhs.mData;
            
            return *this;
        }
        
        BindingPoint & operator = (BindingPoint && rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            
            mData.reset(rhs.mData.release());
            
            return *this;
        }

        BindingType type () const
        {
            return mData->mType;
        }
        
        int device () const
        {
            return mData->mDevice;
        }
        
        int axis () const
        {
            return mData->mAxis;
        }
        
        int code () const
        {
            return mData->mCode;
        }
        
        bool isEventType () const
        {
            return static_cast<unsigned int>(mData->mType) < static_cast<unsigned int>(sf::Event::Count);
        }

    private:
        struct BindingPointData
        {
            BindingType mType;
            
            // The device, axis, and code mean different things depending on the type.
            // For event processing, these can be set to -1 to match any event. But for
            // real-time detection, -1 is not allowed.
            
            // Joystick: This is the device id. Set to -1 to mean any joystick event.
            int mDevice;
            
            // This means different things depending on the type:
            // MouseWheel: This is the wheel code. Set to -1 to mean any wheel event.
            // JoystickMove: This is the axis code. Set to -1 to mean any axis event.
            int mAxis;
            
            // This means different things depending on the type:
            // KeyboardKey: This is the key code. Set to -1 to mean any key event.
            // MouseButton: This is the button code. Set to -1 to mean any button event.
            // JoystickButton: This is the button code. Set to -1 to mean any button event.
            // Touch: This is the finger code. Set to -1 to mean any finger event.
            // Sensor: This is the sensor code. Set to -1 to mean any sensor event.
            int mCode;
            
            BindingPointData (BindingType type, int device, int axis, int code)
            : mType(type), mDevice(device), mAxis(axis), mCode(code)
            { }
            
            BindingPointData (const BindingPointData & src)
            : mType(src.mType), mDevice(src.mDevice), mAxis(src.mAxis), mCode(src.mCode)
            { }
            
            ~BindingPointData ()
            { }
            
            BindingPointData & operator = (const BindingPointData & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }
                
                mType = rhs.mType;
                mDevice = rhs.mDevice;
                mAxis = rhs.mAxis;
                mCode = rhs.mCode;
                
                return *this;
            }
        };
        
        std::unique_ptr<BindingPointData> mData;
    };
    
    class EventDetails
    {
    public:
        EventDetails (const std::string & name)
        : mData(new EventDetailsData(name))
        { }
        
        EventDetails (const EventDetails & src)
        : mData(new EventDetailsData(*src.mData))
        { }
        
        EventDetails (EventDetails && src)
        : mData(src.mData.release())
        { }
        
        ~EventDetails ()
        { }
        
        void swap (EventDetails & other)
        {
            std::unique_ptr<EventDetailsData> thisData(mData.release());
            std::unique_ptr<EventDetailsData> otherData(other.mData.release());
            
            mData.reset(otherData.release());
            other.mData.reset(thisData.release());
        }
        
        EventDetails & operator = (const EventDetails & rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            
            *mData = *rhs.mData;
            
            return *this;
        }
        
        EventDetails & operator = (EventDetails && rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            
            mData.reset(rhs.mData.release());
            
            return *this;
        }
        
        std::string name () const
        {
            return mData->mName;
        }
        
        bool hasSize () const
        {
            return mData->mHasSize;
        }
        
        sf::Event::SizeEvent size () const
        {
            return mData->mSize;
        }
        
        void setSize (const sf::Event::SizeEvent & event)
        {
            mData->mSize = event;
            mData->mHasSize = true;
        }
        
        bool hasKey () const
        {
            return mData->mHasKey;
        }
        
        sf::Event::KeyEvent key () const
        {
            return mData->mKey;
        }
        
        void setKey (const sf::Event::KeyEvent & event)
        {
            mData->mKey = event;
            mData->mHasKey = true;
        }
        
        bool hasText () const
        {
            return mData->mHasText;
        }
        
        sf::Event::TextEvent text () const
        {
            return mData->mText;
        }
        
        void setText (const sf::Event::TextEvent & event)
        {
            mData->mText = event;
            mData->mHasText = true;
        }
        
        bool hasMouseMove () const
        {
            return mData->mHasMouseMove;
        }
        
        sf::Event::MouseMoveEvent mouseMove () const
        {
            return mData->mMouseMove;
        }
        
        void setMouseMove (const sf::Event::MouseMoveEvent & event)
        {
            mData->mMouseMove = event;
            mData->mHasMouseMove = true;
        }
        
        bool hasMouseButton () const
        {
            return mData->mHasMouseButton;
        }
        
        sf::Event::MouseButtonEvent mouseButton () const
        {
            return mData->mMouseButton;
        }
        
        void setMouseButton (const sf::Event::MouseButtonEvent & event)
        {
            mData->mMouseButton = event;
            mData->mHasMouseButton = true;
        }
        
        bool hasMouseWheel () const
        {
            return mData->mHasMouseWheel;
        }
        
        sf::Event::MouseWheelScrollEvent mouseWheel () const
        {
            return mData->mMouseWheel;
        }
        
        void setMouseWheel (const sf::Event::MouseWheelScrollEvent & event)
        {
            mData->mMouseWheel = event;
            mData->mHasMouseWheel = true;
        }
        
        bool hasJoystickMove () const
        {
            return mData->mHasJoystickMove;
        }
        
        sf::Event::JoystickMoveEvent joystickMove () const
        {
            return mData->mJoystickMove;
        }
        
        void setJoystickMove (const sf::Event::JoystickMoveEvent & event)
        {
            mData->mJoystickMove = event;
            mData->mHasJoystickMove = true;
        }
        
        bool hasJoystickButton () const
        {
            return mData->mHasJoystickButton;
        }
        
        sf::Event::JoystickButtonEvent joystickButton () const
        {
            return mData->mJoystickButton;
        }
        
        void setJoystickButton (const sf::Event::JoystickButtonEvent & event)
        {
            mData->mJoystickButton = event;
            mData->mHasJoystickButton = true;
        }
        
        bool hasJoystickConnect () const
        {
            return mData->mHasJoystickConnect;
        }
        
        sf::Event::JoystickConnectEvent joystickConnect () const
        {
            return mData->mJoystickConnect;
        }
        
        void setJoystickConnect (const sf::Event::JoystickConnectEvent & event)
        {
            mData->mJoystickConnect = event;
            mData->mHasJoystickConnect = true;
        }
        
        bool hasTouch () const
        {
            return mData->mHasTouch;
        }
        
        sf::Event::TouchEvent touch () const
        {
            return mData->mTouch;
        }
        
        void setTouch (const sf::Event::TouchEvent & event)
        {
            mData->mTouch = event;
            mData->mHasTouch = true;
        }
        
        bool hasSensor () const
        {
            return mData->mHasSensor;
        }
        
        sf::Event::SensorEvent sensor () const
        {
            return mData->mSensor;
        }
        
        void setSensor (const sf::Event::SensorEvent & event)
        {
            mData->mSensor = event;
            mData->mHasSensor = true;
        }
        
        void clear ()
        {
            mData->mHasSize = false;
            mData->mHasKey = false;
            mData->mHasText = false;
            mData->mHasMouseMove = false;
            mData->mHasMouseButton = false;
            mData->mHasMouseWheel = false;
            mData->mHasJoystickMove = false;
            mData->mHasJoystickButton = false;
            mData->mHasJoystickConnect = false;
            mData->mHasTouch = false;
            mData->mHasSensor = false;
        }
        
    private:
        struct EventDetailsData
        {
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
            
            EventDetailsData (const std::string & name)
            : mName(name), mHasSize(false), mHasKey(false), mHasText(false),
            mHasMouseMove(false), mHasMouseButton(false), mHasMouseWheel(false),
            mHasJoystickMove(false), mHasJoystickButton(false), mHasJoystickConnect(false),
            mHasTouch(false), mHasSensor(false)
            { }
            
            EventDetailsData (const EventDetailsData & src)
            : mName(src.mName), mHasSize(src.mHasSize), mHasKey(src.mHasKey), mHasText(src.mHasText),
            mHasMouseMove(src.mHasMouseMove), mHasMouseButton(src.mHasMouseButton), mHasMouseWheel(src.mHasMouseWheel),
            mHasJoystickMove(src.mHasJoystickMove), mHasJoystickButton(src.mHasJoystickButton), mHasJoystickConnect(src.mHasJoystickConnect),
            mHasTouch(src.mHasTouch), mHasSensor(src.mHasSensor)
            {
                if (mHasSize)
                {
                    mSize = src.mSize;
                }
                if (mHasKey)
                {
                    mKey = src.mKey;
                }
                if (mHasText)
                {
                    mText = src.mText;
                }
                if (mHasMouseMove)
                {
                    mMouseMove = src.mMouseMove;
                }
                if (mHasMouseButton)
                {
                    mMouseButton = src.mMouseButton;
                }
                if (mHasMouseWheel)
                {
                    mMouseWheel = src.mMouseWheel;
                }
                if (mHasJoystickMove)
                {
                    mJoystickMove = src.mJoystickMove;
                }
                if (mHasJoystickButton)
                {
                    mJoystickButton = src.mJoystickButton;
                }
                if (mHasJoystickConnect)
                {
                    mJoystickConnect = src.mJoystickConnect;
                }
                if (mHasTouch)
                {
                    mTouch = src.mTouch;
                }
                if (mHasSensor)
                {
                    mSensor = src.mSensor;
                }
            }
            
            ~EventDetailsData ()
            { }
            
            EventDetailsData & operator = (const EventDetailsData & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }
                
                mName = rhs.mName;
                
                mHasSize = rhs.mHasSize;
                if (mHasSize)
                {
                    mSize = rhs.mSize;
                }
                mHasKey = rhs.mHasKey;
                if (mHasKey)
                {
                    mKey = rhs.mKey;
                }
                mHasText = rhs.mHasText;
                if (mHasText)
                {
                    mText = rhs.mText;
                }
                mHasMouseMove = rhs.mHasMouseMove;
                if (mHasMouseMove)
                {
                    mMouseMove = rhs.mMouseMove;
                }
                mHasMouseButton = rhs.mHasMouseButton;
                if (mHasMouseButton)
                {
                    mMouseButton = rhs.mMouseButton;
                }
                mHasMouseWheel = rhs.mHasMouseWheel;
                if (mHasMouseWheel)
                {
                    mMouseWheel = rhs.mMouseWheel;
                }
                mHasJoystickMove = rhs.mHasJoystickMove;
                if (mHasJoystickMove)
                {
                    mJoystickMove = rhs.mJoystickMove;
                }
                mHasJoystickButton = rhs.mHasJoystickButton;
                if (mHasJoystickButton)
                {
                    mJoystickButton = rhs.mJoystickButton;
                }
                mHasJoystickConnect = rhs.mHasJoystickConnect;
                if (mHasJoystickConnect)
                {
                    mJoystickConnect = rhs.mJoystickConnect;
                }
                mHasTouch = rhs.mHasTouch;
                if (mHasTouch)
                {
                    mTouch = rhs.mTouch;
                }
                mHasSensor = rhs.mHasSensor;
                if (mHasSensor)
                {
                    mSensor = rhs.mSensor;
                }
                return *this;
            }
        };
        
        std::unique_ptr<EventDetailsData> mData;
    };
    
    using BindingPoints = std::vector<BindingPoint>;
    using BindingEventParameter = const EventDetails &;
    using BindingEvent = EventPublisher<BindingEventParameter>;

    Binding (const std::string & name)
    : mData(new BindingData(name))
    { }
    
    Binding (const Binding & src)
    : mData(new BindingData(*src.mData))
    { }
    
    Binding (Binding && src)
    : mData(src.mData.release())
    { }
    
    ~Binding ()
    { }
    
    void swap (Binding & other)
    {
        std::unique_ptr<BindingData> thisData(mData.release());
        std::unique_ptr<BindingData> otherData(other.mData.release());
        
        mData.reset(otherData.release());
        other.mData.reset(thisData.release());
    }
    
    Binding & operator = (const Binding & rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        
        *mData = *rhs.mData;
        
        return *this;
    }
    
    Binding & operator = (Binding && rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        
        mData.reset(rhs.mData.release());
        
        return *this;
    }
    
    std::string name () const
    {
        return mData->mName;
    }
    
    void addBindingPoint (const BindingPoint & bindingPoint)
    {
        mData->mBindingPoints.push_back(bindingPoint);
    }
    
    std::shared_ptr<BindingEvent> eventMatchedEvent ()
    {
        return mData->mEventMatchedEvent;
    }
    
    void handleEvent (const sf::Event & event)
    {
        BindingType sfmlEventType = static_cast<BindingType>(event.type);
        for (auto & bindingPoint: mData->mBindingPoints)
        {
            if (bindingPoint.type() != sfmlEventType)
            {
                continue;
            }
            if (sfmlEventType == BindingType::KeyboardKeyPressed ||
                sfmlEventType == BindingType::KeyboardKeyReleased)
            {
                if (bindingPoint.code() == -1 || bindingPoint.code() == event.key.code)
                {
                    mData->mDetails.setKey(event.key);
                    ++mData->mBindingPointMatches;
                }
                break;
            }
            else if (sfmlEventType == BindingType::MouseButtonPressed ||
                     sfmlEventType == BindingType::MouseButtonReleased)
            {
                if (bindingPoint.code() == -1 || bindingPoint.code() == event.mouseButton.button)
                {
                    mData->mDetails.setMouseButton(event.mouseButton);
                    ++mData->mBindingPointMatches;
                }
                break;
            }
            else if (sfmlEventType == BindingType::MouseWheelScrolled)
            {
                if (bindingPoint.axis() == -1 || bindingPoint.axis() == event.mouseWheelScroll.wheel)
                {
                    mData->mDetails.setMouseWheel(event.mouseWheelScroll);
                    ++mData->mBindingPointMatches;
                }
                break;
            }
            else if (sfmlEventType == BindingType::JoystickButtonPressed ||
                     sfmlEventType == BindingType::JoystickButtonReleased)
            {
                if (bindingPoint.device() == -1 || bindingPoint.device() == event.joystickButton.joystickId)
                {
                    if (bindingPoint.code() == -1 || bindingPoint.code() == event.joystickButton.button)
                    {
                        mData->mDetails.setJoystickButton(event.joystickButton);
                        ++mData->mBindingPointMatches;
                    }
                }
                break;
            }
            else if (sfmlEventType == BindingType::JoystickMoved)
            {
                if (bindingPoint.device() == -1 || bindingPoint.device() == event.joystickMove.joystickId)
                {
                    mData->mDetails.setJoystickMove(event.joystickMove);
                    ++mData->mBindingPointMatches;
                }
                break;
            }
            else if (sfmlEventType == BindingType::JoystickConnected ||
                     sfmlEventType == BindingType::JoystickDisconnected)
            {
                if (bindingPoint.device() == -1 || bindingPoint.device() == event.joystickConnect.joystickId)
                {
                    mData->mDetails.setJoystickConnect(event.joystickConnect);
                    ++mData->mBindingPointMatches;
                }
                break;
            }
            else if (sfmlEventType == BindingType::TouchBegan ||
                     sfmlEventType == BindingType::TouchMoved ||
                     sfmlEventType == BindingType::TouchEnded)
            {
                if (bindingPoint.code() == -1 || bindingPoint.code() == event.touch.finger)
                {
                    mData->mDetails.setTouch(event.touch);
                    ++mData->mBindingPointMatches;
                }
                break;
            }
            else if (sfmlEventType == BindingType::SensorChanged)
            {
                if (bindingPoint.code() == -1 || bindingPoint.code() == event.sensor.type)
                {
                    mData->mDetails.setSensor(event.sensor);
                    ++mData->mBindingPointMatches;
                }
                break;
            }
            else
            {
                if (sfmlEventType == BindingType::WindowResized)
                {
                    mData->mDetails.setSize(event.size);
                }
                if (sfmlEventType == BindingType::KeyboardTextEntered)
                {
                    mData->mDetails.setText(event.text);
                }
                if (sfmlEventType == BindingType::MouseMoved)
                {
                    mData->mDetails.setMouseMove(event.mouseMove);
                }
                
                ++mData->mBindingPointMatches;
                break;
            }
        }
    }

    void handleCurrentStates (bool checkBindings)
    {
        if (checkBindings)
        {
            for (auto & bindingPoint: mData->mBindingPoints)
            {
                if (bindingPoint.type() == BindingType::CurrentKeyboardKeyPressed)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(bindingPoint.code())))
                    {
                        sf::Event::KeyEvent event;
                        event.alt = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt);
                        event.control = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
                        event.shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
                        event.system = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LSystem) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RSystem);
                        event.code = sf::Keyboard::Key(bindingPoint.code());
                        
                        mData->mDetails.setKey(event);
                        ++mData->mBindingPointMatches;
                    }
                    continue;
                }
                else if (bindingPoint.type() == BindingType::CurrentMouseButtonPressed)
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button(bindingPoint.code())))
                    {
                        sf::Event::MouseButtonEvent event;
                        sf::Vector2i position = sf::Mouse::getPosition();
                        event.x = position.x;
                        event.y = position.y;
                        event.button = sf::Mouse::Button(bindingPoint.code());
                        
                        mData->mDetails.setMouseButton(event);
                        ++mData->mBindingPointMatches;
                    }
                    continue;
                }
                else if (bindingPoint.type() == BindingType::CurrentJoystickButtonPressed)
                {
                    if (sf::Joystick::isButtonPressed(bindingPoint.device(), bindingPoint.code()))
                    {
                        sf::Event::JoystickButtonEvent event;
                        event.joystickId = bindingPoint.device();
                        event.button = bindingPoint.code();
                        
                        mData->mDetails.setJoystickButton(event);
                        ++mData->mBindingPointMatches;
                    }
                    continue;
                }
            }
        }
        
        if (mData->mBindingPointMatches == mData->mBindingPoints.size())
        {
            mData->mEventMatchedEvent->signal(mData->mDetails);
        }
        
        mData->mBindingPointMatches = 0;
        mData->mDetails.clear();
    }
    
private:
    struct BindingData
    {
        std::string mName;
        EventDetails mDetails;
        BindingPoints mBindingPoints;
        unsigned int mBindingPointMatches;
        std::shared_ptr<BindingEvent> mEventMatchedEvent;
        
        BindingData (const std::string & name)
        : mName(name), mDetails(name), mBindingPointMatches(0), mEventMatchedEvent(new BindingEvent())
        { }
        
        BindingData (const BindingData & src)
        : mName(src.mName), mDetails(src.mDetails), mBindingPoints(src.mBindingPoints),
        mBindingPointMatches(src.mBindingPointMatches), mEventMatchedEvent(src.mEventMatchedEvent)
        { }
        
        ~BindingData ()
        { }
        
        BindingData & operator = (const BindingData & rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }
            
            mName = rhs.mName;
            mDetails = rhs.mDetails;
            mBindingPoints = rhs.mBindingPoints;
            mBindingPointMatches = rhs.mBindingPointMatches;
            mEventMatchedEvent = rhs.mEventMatchedEvent;
            
            return *this;
        }
    };
    
    std::unique_ptr<BindingData> mData;
};
