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


class Window
{
public:
    explicit Window ();
    Window (const std::string & title, const sf::Vector2u & size);
    ~Window ();
    
    void drawBegin ();
    void drawEnd ();
    void draw (const sf::Drawable & obj);
    void update ();
    
    void toggleFullScreen ();
    
    std::string title () const;
    sf::Vector2u size () const;
    bool isDone () const;
    bool isFullScreen () const;
    
private:
    void create ();
    void destroy ();
    
    sf::RenderWindow mWindow;
    std::string mTitle;
    sf::Vector2u mSize;
    bool mDone;
    bool mFullScreen;
};