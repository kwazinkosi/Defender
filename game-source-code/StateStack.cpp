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

void StateStack::handleRealtimeInput(sf::RenderWindow & window)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        //if state == GameState
        if ((*itr)->getStateID() == getStateName(States::GameState))
        {
            //std::cout << "StateStack::handleRealtimeInput()::GameState" << std::endl;   
            (*itr)->handleRealtimeInput(window);
        }
    }
    // This means that the state's handleEvent() function has returned true, so the event is handled.
    applyPendingChanges();
}
/**
 * @brief Pushes a new state to the stack.
 *
 * - This function pushes a new state to the stack by adding the push action to the mPendingList vector.
 */
void StateStack:: pushState(States stateID)
{
    PendingChange change;
    change.action = StackAction::Push;
    change.stateID = stateID;
    mPendingList.push_back(change);
}

/**
 * @brief Pops the top state from the stack.
 *
 * - popState() pops the top state from the stack by adding the pop action to the mPendingList vector.
 */
void StateStack::popState()
{
    PendingChange change;
    change.action = StackAction::Pop;
    mPendingList.push_back(change);
}
/**
 * @brief Clears all the states from the stack.
 *
 * - clearStates() clears all the states from the stack by adding the clear action to the mPendingList vector.
 */
void StateStack::clearStates()
{
    PendingChange change;
    change.action = StackAction::Clear;
    mPendingList.push_back(change);
}

/**
 * @brief Checks if the stack is empty.
 *
 * @return true If the stack vector is empty, false otherwise.
 */
bool StateStack::isEmpty() const
{
    // Returns true if the vector is empty, false otherwise.
    return mStack.empty();
}
// Private functions
/**
 * @brief Creates a new state and adds it to the stack.
 *
 * - The stateID is used to find the corresponding lambda function in the mFactories map.
 * - The lambda function creates a new state and returns a pointer to it, which is then added to the stack.
 * - This function is called by pushState().
 *
 * @param stateID The ID of the state to be created (see StateIdentifiers.hpp).
 * @return State::Ptr
 */
State::Ptr StateStack::createState(States stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    return found->second(); // Calls the lambda function stored in the map that corresponds
                            // to the stateID and creates a new state.
}
/**
 * @brief Applies any pending changes to the stack.
 *
 * - This function iterates through each pending change in the mPendingList vector and applies it to the stack.
 * - If the action is Push, then a new state is created and added to the stack.
 * - If the action is Pop, then the top state is removed from the stack, and the state below it becomes the active state.
 */
void StateStack::applyPendingChanges()
{
    for (PendingChange change : mPendingList)
    {
        switch (change.action)
        {
        case StackAction::Push:
            mStack.push_back(createState(change.stateID)); // Creates a new state and adds it to the stack.
            break;
        case StackAction::Pop:
            mStack.pop_back(); // Removes the top state from the stack.
            break;
        case StackAction::Clear:
            mStack.clear(); // Removes all the states from the stack.
            break;
        }
    }
    mPendingList.clear(); // Clears the pending list.
}
/**
 * @brief Returns the name of the state.
 *
 * @param stateID The ID of the state (see StateIdentifiers.hpp).
 * @return std::string
 */
std::string StateStack::getStateName(States stateID) const
{
    switch (stateID)
    {
    case States::LoadingState:
        return "LoadingState";
    case States::SplashState:
        return "SplashState";
    case States::MainMenuState:
        return "MainMenuState";
    case States::GameState:
        return "GameState";
    case States::HelpState:
        return "HelpState";
    case States::GameOverState:
        return "GameOverState";
    case States::PauseState:
        return "PauseState";
    case States::ScoreState:
        return "ScoreState";
    default:
        return "Unknown state";
    }
    return "Unknown state";
}

bool StateStack::hasState(States stateID) const
{
     for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if ((*itr)->getStateID() == getStateName(stateID))
        {
            return true;
        }
    }
    return false;
}

