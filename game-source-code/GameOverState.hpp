#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include <memory>
#include "State.hpp"
#include "TextFormater.hpp"

class GameOverState : public State
{
    public:
        GameOverState(StateStack& stack, Context &context);

    private:
        Context* mContext;
        sf::RectangleShape backgroundShape;
        sf::Text mGameOverText;
        sf::Text mInstructionText;
        TextFormater mTextFormater;

};
#endif

