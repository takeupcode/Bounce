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
    Window (const std::string & title, unsigned int width, unsigned int height);
    ~Window ();
    
    void drawBegin ();
    void drawEnd ();
    void draw (const sf::Drawable & obj);
    void update ();
    
    void toggleFullScreen ();
    
    std::string title () const;
    unsigned int width () const;
    unsigned int height () const;
    bool isDone () const;
    bool isFullScreen () const;
    
private:
    void create ();
    void destroy ();
    
    sf::RenderWindow mWindow;
    std::string mTitle;
    unsigned int mWidth;
    unsigned int mHeight;
    bool mDone;
    bool mFullScreen;
};