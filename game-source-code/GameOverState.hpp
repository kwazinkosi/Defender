#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include <memory>
#include "State.hpp"
#include "TextFormater.hpp"

class GameOverState : public State
{
    public:
        GameOverState(StateStack& stack, Context &context);
        ~GameOverState();
        virtual void draw(sf::RenderWindow &window);
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        virtual void handleRealtimeInput(sf::RenderWindow &window);
        virtual std::string getStateID() const;
        void onActivate();

    private:
        Context* mContext;
        sf::RectangleShape backgroundShape;
        sf::Text mGameOverText;
        sf::Text mInstructionText;
        TextFormater mTextFormater;

};
#endif

