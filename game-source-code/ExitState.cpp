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
    
}

bool ExitState::handleEvent(const sf::Event &event)
{
    
}

void ExitState::handleRealtimeInput(sf::RenderWindow &window)
{
}
