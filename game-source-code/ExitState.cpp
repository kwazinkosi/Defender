#include "ExitState.hpp"

ExitState::ExitState(StateStack &stack, Context &context)
:State(stack, context)
{
    //ctor
    requestStateClear();//clear the stack, so that the game exits
}

void ExitState::draw(sf::RenderWindow &target)
{
}

bool ExitState::update(sf::Time dt)
{
    return true;
}

bool ExitState::handleEvent(const sf::Event &event)
{
 return true;   
}

void ExitState::handleRealtimeInput(sf::RenderWindow &window)
{
}
