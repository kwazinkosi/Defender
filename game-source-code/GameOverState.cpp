#include "GameOverState.hpp"

GameOverState::GameOverState(StateStack& stack, Context &context)
{
}

void GameOverState::draw(sf::RenderWindow &window)
{
}

bool GameOverState::update(sf::Time dt)
{
    return false;
}

bool GameOverState::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    return false;
}

void GameOverState::handleRealtimeInput(sf::RenderWindow &window)
{
}

std::string GameOverState::getStateID() const
{
    return std::string();
}

void GameOverState::onActivate()
{
}
