#include "ExitState.hpp"

ExitState::ExitState(StateStack &stack, Context &context)
:State(stack, context)
{
    //ctor
    requestStateClear();//clear the stack, so that the game exits
}
