#include "StateStack.hpp"
/**
 * @brief Construct a new State Stack:: State Stack object  (default constructor).
 *
 */
StateStack::StateStack()
{
}

// Public functions
/**
 * @brief Updates the game state.
 *
 * - This function updates the game state by iterating through each state in the stack and updating it.
 * - The function also applies any pending changes to the stack if there are any.
 *
 * @param dt The time elapsed since the last iteration of the game loop.
 */
void StateStack::update(sf::Time dt)
{
    
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->update(dt))
        {
            break; // If the state returns false, then it means that it doesn't want the states below it to be updated.
        }
    }
    applyPendingChanges();
}