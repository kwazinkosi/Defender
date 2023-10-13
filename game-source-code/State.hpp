#ifndef STATE_HPP
#define STATE_HPP

#include "StateIdentifiers.hpp"
#include "ResourceManager.hpp"
#include <memory>
#include <string>
#include "Context.hpp"

class StateStack;
/**
 * @brief The State class is an abstract base class for all game states.
 */
class State
{
    public:
        typedef std::unique_ptr<State> Ptr;

    public: 
        /**
         * @brief Construct a new State object
         * 
         * @param stack The state stack
         * @param context The context
         */
        explicit State(StateStack &stack, Context &context);

        /**
         * @brief Destroy the State object
         * 
         */
        virtual ~State();

        /**
         * @brief Draw the state
         * 
         * @param window The render window
         */
        virtual void draw(sf::RenderWindow &window) = 0;

        /**
         * @brief Update the state
         * 
         * @param dt The time elapsed since the last update
         * @return true if the state should continue to be updated, false otherwise
         */
        virtual bool update(sf::Time dt) = 0;

        /**
         * @brief Handle an event
         * 
         * @param event The event to handle
         * @param window The render window
         * @return true if the event was handled, false otherwise
         */
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window) = 0;

        /**
         * @brief Handle realtime input
         * 
         * @param window The render window
         */
        virtual void handleRealtimeInput(sf::RenderWindow &window) = 0;

        /**
         * @brief Get the state ID
         * 
         * @return The state ID
         */
        virtual std::string getStateID() const = 0;
    
     protected: 
        /**
         * @brief Request to push a new state onto the stack
         * 
         * @param stateID The ID of the state to push
         */
        void requestStackPush(States stateID);

        /**
         * @brief Request to pop the current state from the stack
         * 
         */
        void requestStackPop();

        /**
         * @brief Request to clear the state stack
         * 
         */
        void requestStateClear();


    private: // Private because derived classes don't need to access it.
        StateStack *mStack; /**< Pointer to the state stack, used to request changes to the stack. */
        Context *mContext; /**< Context used to share resources between states. */
};

#endif // STATE_HPP  