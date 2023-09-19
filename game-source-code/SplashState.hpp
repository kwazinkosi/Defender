#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP

#include "State.hpp"
#include "StateStack.hpp"
#include "TextFormater.hpp"

class SplashState : public State
{
    public:
        SplashState(StateStack &stack, Context &context);

        //virtual because we are overriding the virtual functions in the State class
        virtual void draw(sf::RenderWindow &window);
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        virtual void handleRealtimeInput(sf::RenderWindow &window) ;
        virtual std::string getStateID() const;

    private:
        bool mShowText;
        sf::Sprite mBackgroundSprite;
        //sf::Sprite mKeypadSprite;
        sf::Texture mTexture;
        sf::Text mText;
        sf::Time mElapsedTime;

        TextFormater mTextFormater;
        
};

#endif // SPLASHSTATE_HPP