//
//  Window.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Window.h"

Window::Window ()
: mTitle("GameWindow"), mSize(800, 600), mDone(false), mFullScreen(false)
{
    create();
}

Window::Window (const std::string & title, const sf::Vector2u & size)
: mTitle(title), mSize(size), mDone(false), mFullScreen(false)
{
    create();
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

void Window::update ()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mDone = true;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
        {
            toggleFullScreen();
        }
    }
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

void Window::create ()
{
    auto style = mFullScreen ? sf::Style::Fullscreen : sf::Style::Default;
    mWindow.create({mSize.x, mSize.y}, mTitle, style);
}

void Window::destroy ()
{
    mWindow.close();
}
