#ifndef STATE_HPP
#define STATE_HPP

#include "StateIdentifiers.hpp"
#include "ResourceManager.hpp"
#include <memory>
#include <string>

class State
{
    public:
        typedef std::unique_ptr<State> Ptr;

    public: 
    //explicit because we don't want implicit conversions from StateStack to State, preventing the user from doing something like this: mStateStack.pushState(States::Game);
        State(StateStack &stack, Context &context);
        virtual ~State();
        virtual void draw(sf::RenderWindow &window) = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window) = 0;
        virtual std::string getStateID() const = 0;
    
     protected: 
        Context *mContext; //Context used to share resources between states.
        void requestStackPush(States stateID);
        void requestStackPop();
        void requestStateClear();


    private: // Private because derived classes don't need to access it.
        StateStack *mStack; //Pointer to the state stack, used to request changes to the stack.
};

#endif // STATE_HPP  