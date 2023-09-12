#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "Player.hpp"
#include "StateStack.hpp"
#include "Context.hpp"   
#include "PauseState.hpp"

//this is the game state class. It is the state where the game is played, only player 1 is active in this state.
class GameState : public State
{
    public:
        GameState (StateStack& stack, Context &context);
        virtual void draw(sf::RenderWindow& window);
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event, sf::RenderWindow &window);
        virtual std::string getStateID() const;
        
    private:
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        void pauseGame();
        void gameOver();
        sf::Sprite mBackgroundSprite;
        sf::Text mText; 
        bool mIsPaused;
};

#endif 