//
//  ScenePaused.hpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/24/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Scene.h"

class Director;
class Window;

class ScenePaused : public Scene
{
public:
    void created () override;
    
    void destroyed () override;
    
    void activated () override;
    
    void deactivated () override;
    
    void update (float elapsedSeconds) override;
    void render () override;
    
protected:
    friend class SceneManager;
    
    ScenePaused (Director * director, SceneIdentities identity, std::shared_ptr<Window> window, bool transparent, bool modal);
    
    void loadTriggers () override;
    void unloadTriggers () override;
    
    void notify (EventParameter eventDetails) override;
    
private:
    sf::Font mFont;
    sf::Text mText;
};
