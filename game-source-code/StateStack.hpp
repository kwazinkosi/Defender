#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <map>
#include <functional>
#include <cassert>
#include "State.hpp"
#include "ResourceManager.hpp"
#include "Context.hpp"

/**
 * @brief The action to be performed on the state stack.
 */
enum class StackAction
{
    Push,   /**< Push a new state onto the stack. */
    Pop,    /**< Pop the current state from the stack. */
    Clear,  /**< Clear all states from the stack. */
};

/**
 * @brief A stack of game states.
 */
class StateStack
{
public:
   
    template <typename T>
    void registerState(States stateID, Context &context);

    /**
     * @brief Update the current state.
     *
     * @param dt The time elapsed since the last update.
     */
    void update(sf::Time dt);

    /**
     * @brief Draw the current state.
     *
     * @param window The window to draw the state on.
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Handle an event for the current state.
     *
     * @param event The event to handle.
     * @param window The window the event occurred on.
     */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window);

    /**
     * @brief Handle realtime input for the current state.
     *
     * @param window The window to handle input for.
     */
    void handleRealtimeInput(sf::RenderWindow &window);

    /**
     * @brief Push a new state onto the stack.
     *
     * @param stateID The ID of the state to push onto the stack.
     */
    void pushState(States stateID);

    /**
     * @brief Pop the current state from the stack.
     */
    void popState();

    /**
     * @brief Clear all states from the stack.
     */
    void clearStates();

    /**
     * @brief Check if the state stack is empty.
     *
     * @return true if the state stack is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Get the name of a state.
     *
     * @param stateID The ID of the state to get the name of.
     * @return The name of the state.
     */
    std::string getStateName(States stateID) const;

    /**
     * @brief Check if a state is in the stack.
     *
     * @param stateID The ID of the state to check for.
     * @return true if the state is in the stack, false otherwise.
     */
    bool hasState(States stateID) const;

private:
    struct PendingChange
    {
        StackAction action; /**< The action to perform. */
        States stateID;     /**< The ID of the state to perform the action on. */
    };
    State::Ptr createState(States stateID);
    void applyPendingChanges();

    std::vector<State::Ptr> mStack;                           /**< The stack of states, containing pointers to the states' objects. */
    std::vector<PendingChange> mPendingList;                  /**< The list of pending changes to the stack. */
    std::map<States, std::function<State::Ptr()>> mFactories; /**< The map of lambda functions that create new states. */
};

#endif // STATESTACK_HPP