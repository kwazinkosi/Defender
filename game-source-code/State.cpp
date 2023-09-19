#include "State.hpp"
#include "StateStack.hpp"

State::State(StateStack &stack, Context &context) : mContext(&context), mStack(&stack)
{

}

State::~State()
{
}
/**
 * @brief This is a function that is called when the state is pushed onto the stack.
 * 
 * @param stateID  The ID of the state (enum class States::ID)
 */
void State::requestStackPush(States stateID)
{
    mStack->pushState(stateID);
}
/**
 * @brief This function is called when the state is popped from the stack.
 * 
 */
void State::requestStackPop()
{
    mStack->popState();
}
/**
 * @brief This function is called when the state stack is cleared.
 * 
 */
void State::requestStateClear()
{
    mStack->clearStates(); //clears all the states from the stack
}
