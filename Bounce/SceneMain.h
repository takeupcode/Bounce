//
//  SceneMain.h
//  Bounce
//
//  Created by Abdul Wahid Tanner on 8/23/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#pragma once

#include <memory>
#include <random>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../EasySFML/Scene.h"

class Command;
class Director;
class Hero;
class Region;
class SpriteSheet;
class Window;

class SceneMain : public Scene
{
public:
    static const std::string MoveCharacterLeft;
    static const std::string MoveCharacterRight;
    static const std::string MoveCharacterUp;
    static const std::string MoveCharacterDown;

    std::string name () const override
    {
        return "SceneMain";
    }
    
    void created () override;
    
    void update (float elapsedSeconds) override;
    void render () override;
    
protected:
    friend class SceneManager;
    
    SceneMain (Director * director, int identity, std::shared_ptr<Window> window, bool transparent, bool modal);
    
    void createTriggers () override;
    void loadTriggers () override;
    void unloadTriggers () override;
    
    void notify (EventParameter eventDetails) override;
    
private:
    void frameView ();
    
    std::shared_ptr<Hero> mHero;
    std::shared_ptr<SpriteSheet> mTileSheet;
    std::shared_ptr<Region> mRegion;
    std::mt19937 randomGenerator;
    std::uniform_real_distribution<float> uniformDistribution;
    std::vector<std::unique_ptr<Command>> mCommands;
};
