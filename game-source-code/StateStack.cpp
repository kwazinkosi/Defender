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
/**
 * @brief Draws the game state.
 *
 * - This function draws the game state by iterating through each state in the stack and drawing it.
 */
void StateStack::draw(sf::RenderWindow &window)
{
    // Draws the states in the stack from the bottom to the top.
    for (State::Ptr &state : mStack)
    {
        state->draw(window);
    }
}
/**
 * @brief Handles keyboard input for the game state.
 *
 * - The function handles keyboard input by iterating through each state in the stack and handling the event.
 * - The active state is the state at the top of the stack, and it is the only state that can handle events unless it returns false.
 * - The function also applies any pending changes to the stack if there are any.
 *
 * @param event
 */
void StateStack::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        // If the state returns false, then it means that it doesn't want the states below it to handle the event.
        if (!(*itr)->handleEvent(event, window)) // This handleEvent() function is the one that is defined in the State class.
        {
            // This means that the state's handleEvent() function has returned false, so the event is not handled.
            break;
        }
    }
    // This means that the state's handleEvent() function has returned true, so the event is handled.
    applyPendingChanges();
}
