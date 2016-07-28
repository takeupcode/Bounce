//
//  Window.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "BindingManager.h"

class Window : public std::enable_shared_from_this<Window>, public EventSubscriber<Binding::BindingEventParameter>
{
public:
    Window ();
    Window (const std::string & title, const sf::Vector2u & size);
    ~Window ();
    
    void drawBegin ();
    void drawEnd ();
    void draw (const sf::Drawable & obj);
    void handleInput ();
    
    void toggleFullScreen ();
    
    std::string title () const;
    sf::Vector2u size () const;
    bool isDone () const;
    bool isFullScreen () const;
    
    std::shared_ptr<BindingManager> getBindingManager ();
    
    void notify (Binding::BindingEventParameter eventDetails) override;
    
    void loadBindings ();
    
private:
    void create ();
    void destroy ();
    
    sf::RenderWindow mWindow;
    std::string mTitle;
    sf::Vector2u mSize;
    bool mDone;
    bool mFullScreen;
    std::shared_ptr<BindingManager> mBindingManager;
};