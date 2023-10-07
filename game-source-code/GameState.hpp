#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "World.hpp"
#include "State.hpp"
#include "Player.hpp"
#include "Context.hpp" 
#include "Score.hpp"  
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "MainMenuState.hpp"

//this is the game state class. It is the state where the game is played, only player 1 is active in this state.
class GameState : public State
{
    public:
        GameState (StateStack& stack, Context &context);
        virtual void draw(sf::RenderWindow& window);
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event, sf::RenderWindow &window);
        virtual void handleRealtimeInput(sf::RenderWindow &window);
        virtual std::string getStateID() const;
        
    private:
    
        void pauseGame();
        void gameOver();
        std::unique_ptr<World> mWorld; // world
        sf::RenderWindow mWindow; // window
        sf::View mWorldView; // world view
        sf::Clock clock; // clock
        sf::Sprite mBackgroundSprite;
        sf::Text mText; 
        bool mIsPaused;
};

#endif 