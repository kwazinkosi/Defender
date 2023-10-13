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
    /**
     * @brief Construct a new Game State object 
     * 
     * @param stack 
     * @param context 
     */
        GameState (StateStack& stack, Context &context);
        /**
         * @brief  draws the game state to the screen.  
         * 
         * @param window 
         */
        virtual void draw(sf::RenderWindow& window);
        /**
         * @brief  Updates the game state.
         * 
         * @param dt 
         * @return true 
         * @return false 
         */
        virtual bool update(sf::Time dt);
        /**
         * @brief  Handles the game state's input.
         * 
         * @param event 
         * @param window 
         * @return true 
         * @return false 
         */
        virtual bool handleEvent(const sf::Event& event, sf::RenderWindow &window);
        /**
         * @brief  Handles the game state's realtime input.
         * 
         * @param window 
         */
        virtual void handleRealtimeInput(sf::RenderWindow &window);
        /**
         * @brief Get the State I D object
         * 
         * @return std::string 
         */
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