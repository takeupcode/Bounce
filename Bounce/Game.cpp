//
//  Game.cpp
//  Bounce
//
//  Created by Abdul Wahid Tanner on 7/8/16.
//  Copyright © 2016 Take Up Code. All rights reserved.
//

#include "Game.h"

using namespace std;

Game::Game ()
{
}

Game::Game (const std::string & title, const sf::Vector2u & size)
: mWindow(new Window(title, size))
{
    mWindow->loadBindings();
}

Game::~Game ()
{
}

shared_ptr<Window> Game::getWindow ()
{
    return mWindow;
}

const shared_ptr<Window> Game::getWindow () const
{
    return mWindow;
}

void Game::handleInput ()
{
    getWindow()->handleInput();
}

bool Game::isDone () const
{
    return getWindow()->isDone();
}

sf::Time Game::elapsed () const 
{
    return mElapsed;
}

void Game::restartClock ()
{
    mElapsed = mClock.restart();
    mFixedFrameTotal += mElapsed;
}

bool Game::isFixedFrameReady () const
{
    return mFixedFrameTotal.asSeconds() >= mFixedFrameTime;
}

void Game::completeFixedFrame ()
{
    mFixedFrameTotal -= sf::seconds(mFixedFrameTime);
}
