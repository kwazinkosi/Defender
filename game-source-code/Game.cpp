#include "Game.hpp"

Game::Game()
{
    registerStates();
}

Game::~Game()
{
}

void Game::runGame()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mContext.mWindow.isOpen())
    {
        //At this point, a new frame has started, so we need to measure the time elapsed since the last frame. 
        timeSinceLastUpdate += clock.restart();  // restart() returns the time elapsed since the last restart() call
       
        while (timeSinceLastUpdate > mTimePerFrame)
        {
            //At this point, we have accumulated enough time to update the game state.
            timeSinceLastUpdate -= mTimePerFrame;
            processEvents();
            update(mTimePerFrame);  // update() is a private member function of Game that updates the game state
        }
        render(); // render() renders the game state to the window for display

    }
}

void Game::processEvents()
{
}

void Game::update(sf::Time deltaTime)
{
}

void Game::render()
{
}
