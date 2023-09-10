#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <map>
#include <functional>
#include <cassert>
#include "State.hpp"
#include "ResourceManager.hpp"

enum class Action
{
    Push,
    Pop,
    Clear,
};
class StateStackException
{
};

class StateStack
{
public:
    explicit StateStack(); // we don't want implicit conversions from StateStack to State, preventing the user from doing something like this: mStateStack.pushState(States::Game);
    template <typename T>
    void registerState(States stateID, Context &context);
    void update(sf::Time dt);
    void draw(sf::RenderWindow &window);
    void handleEvent(const sf::Event &event, sf::RenderWindow &window);
    void pushState(States stateID);
    void popState();
    void clearStates();
    bool isEmpty() const;
    std::string getStateName(States stateID) const;
    bool hasState(States stateID) const;

private:
    struct PendingChange
    {
        Action action;
        States stateID;
    };

private:
    State::Ptr createState(States stateID);
    void applyPendingChanges();

    std::vector<State::Ptr> mStack;                           // The stack of states, containing pointers to the states' objects.
    std::vector<PendingChange> mPendingList;                  // The list of pending changes to the stack.
    std::map<States, std::function<State::Ptr()>> mFactories; // The map of lambda functions that create new states.
};
/**
 * @brief Registers a new state to the state stack.
 *
 * - The main purpose of this function is to register a new state to the state stack so that it can be created later in createState().
 * - The state is registered by storing a lambda function in the mFactories map.
 * - The lambda function creates a new state and returns a pointer to it.
 *
 * @tparam T The type of the state to be registered (e.g., MenuState).
 * @param stateID The ID of the state to be registered (e.g., States::Menu)
 */
template <typename T>
void StateStack::registerState(States stateID, Context &context)
{
    std::cout << "Registering " << getStateName(stateID) << "\n";
    mFactories[stateID] = [this, &context]() // The lambda function that creates a new state and returns a pointer to it.
    {
        auto ptr = std::make_unique<T>(*this, context); // Create a new state and store a pointer to a T(e.g., MenuState) object in ptr.
        return ptr;
    };
}

#endif // STATESTACK_HPP