#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include "ResourceManager.hpp"
#include "State.hpp"
#include "StateStack.hpp"

class  LoadingState : public State  
{
    public:
        LoadingState(StateStack& stack, Context &context);

        virtual void draw(sf::RenderWindow &window);
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        virtual std::string getStateID() const;

    private:

        sf::Font mLoadingFont;
        sf::Text mLoadingText;
        sf::Time mElapsedTime; // The elapsed time since the last update
        sf::RectangleShape mProgressBarBackground;
        sf::RectangleShape mProgressBar;
        sf::RectangleShape mBackground; // The background of the loading screen
        std::string mLoadingString; // The string that is displayed on the loading screen
        //Functions 
        void centerOrigin(sf::Text& text);
        void setCompletion(float percent); // 0 - 1
        void executeLoadingTask(sf::RenderWindow &window); // To execute the loading task
};

#endif 