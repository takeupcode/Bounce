//
//  SceneMainMenu.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Scene.h"

class Director;
class Window;

class SceneMainMenu : public Scene
{
public:
    void created () override;
    
    void activated () override;
    
    void update (float elapsedSeconds) override;
    void render () override;
    
protected:
    friend class SceneManager;
    
    SceneMainMenu (Director * director, SceneIdentities identity, std::shared_ptr<Window> window, bool transparent, bool modal);
    
    void loadTriggers () override;
    void unloadTriggers () override;
    
    void notify (EventParameter eventDetails) override;
    
private:
    sf::Font mFont;
    sf::Text mMenuTitle;
    
    sf::Vector2f mButtonSize;
    sf::Vector2f mButtonPosition;
    unsigned int mButtonPadding;
    
    sf::RectangleShape mButtons[3];
    sf::Text mButtonText[3];
};
