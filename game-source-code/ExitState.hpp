#ifndef EXITSTATE_HPP
#define EXITSTATE_HPP

#include "State.hpp"

//this class is used to exit the game. It only requests the stack to be cleared.

class ExitState : public State
{
    public:
        ExitState(StateStack &stack, Context &context);

        virtual void draw(sf::RenderWindow &target);
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event &event);
};
#endif // EXITSTATE_HPP