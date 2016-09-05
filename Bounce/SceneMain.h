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
class Dot;
class Window;

class SceneMain : public Scene
{
public:
    static const std::string MoveCharacterLeft;
    static const std::string MoveCharacterRight;
    static const std::string MoveCharacterUp;
    static const std::string MoveCharacterDown;

    void created () override;
    
    void update (float elapsedSeconds) override;
    void render () override;
    
protected:
    friend class SceneManager;
    
    SceneMain (Director * director, int identity, std::shared_ptr<Window> window, bool transparent, bool modal);
    
    void loadTriggers () override;
    void unloadTriggers () override;
    
    void notify (EventParameter eventDetails) override;
    
private:
    std::shared_ptr<Dot> mDot;
    std::mt19937 randomGenerator;
    std::uniform_real_distribution<float> uniformDistribution;
    std::vector<std::unique_ptr<Command>> mCommands;
};
