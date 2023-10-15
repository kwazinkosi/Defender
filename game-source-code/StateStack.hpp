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
    /**
     * @brief Construct a new StateStack object.
     */
    explicit StateStack();

    /**
     * @brief Registers a new state to the state stack.
     *
     * The main purpose of this function is to register a new state to the state stack so that it can be created later in createState().
     * The state is registered by storing a lambda function in the mFactories map.
     * The lambda function creates a new state and returns a pointer to it.
     *
     * @tparam T The type of the state to be registered (e.g., MenuState).
     * @param stateID The ID of the state to be registered (e.g., States::Menu)
     * @param context The context object to be passed to the state's constructor.
     */
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