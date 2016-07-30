//
//  Window.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Window.h"

using namespace std;

Window::Window ()
: mTitle("GameWindow"), mSize(800, 600), mDone(false), mFullScreen(false)
{
    create();
}

Window::Window (const std::string & title, const sf::Vector2u & size)
: mTitle(title), mSize(size), mDone(false), mFullScreen(false), mEventManager(new EventManager())
{
    create();
    
    mEventManager->loadTriggers();
}

Window::~Window ()
{
    destroy();
}

void Window::drawBegin ()
{
    mWindow.clear(sf::Color::Black);
}

void Window::drawEnd ()
{
    mWindow.display();
}

void Window::draw (const sf::Drawable & obj)
{
    mWindow.draw(obj);
}

void Window::handleInput ()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mEventManager->handleEvent(event);
    }
    
    mEventManager->handleCurrentStates();
}

void Window::toggleFullScreen ()
{
    mFullScreen = !mFullScreen;
    destroy();
    create();
}

std::string Window::title () const
{
    return mTitle;
}

sf::Vector2u Window::size () const
{
    return mSize;
}

bool Window::isDone () const
{
    return mDone;
}

bool Window::isFullScreen () const
{
    return mFullScreen;
}

std::shared_ptr<EventManager> Window::getEventManager ()
{
    return mEventManager;
}

void Window::notify (Trigger::EventParameter eventDetails)
{
    if (eventDetails.name() == EventManager::WindowClosed)
    {
        mDone = true;
    }
    else if (eventDetails.name() == EventManager::WindowToggleFullScreen)
    {
        toggleFullScreen();
    }
}

void Window::loadTriggers()
{
    mEventManager->addSubscription(EventManager::WindowClosed, "Window", shared_from_this());
    mEventManager->addSubscription(EventManager::WindowToggleFullScreen, "Window", shared_from_this());
}

void Window::create ()
{
    auto style = mFullScreen ? sf::Style::Fullscreen : sf::Style::Default;
    mWindow.create({mSize.x, mSize.y}, mTitle, style);
    mWindow.setFramerateLimit(60);
}

void Window::destroy ()
{
    mWindow.close();
}
