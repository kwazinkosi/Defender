#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "State.hpp"
#include "TextFormater.hpp"

class PauseState : public State
{
    public:
        PauseState(StateStack& stack, Context &context);

        virtual void draw(sf::RenderWindow &window);
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        virtual std::string getStateID() const;
        
    private:
        sf::RectangleShape backgroundShape;
        sf::Text mPausedText;
        sf::Text mInstructionText;
        TextFormater mTextFormater;
};
#endif // PAUSESTATE_HPP
