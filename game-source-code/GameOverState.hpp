#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include <memory>
#include "State.hpp"
#include "TextFormater.hpp"

class GameOverState : public State
{
    public:
        /**
         * @brief Construct a new Game Over State object 
         * 
         * @param stack 
         * @param context 
         */
        GameOverState(StateStack& stack, Context &context);
        /**
         * @brief Destroy the Game Over State object
         * 
         */
        ~GameOverState();
        /**
         * @brief  draws the game over state to the screen.
         * 
         * @param window 
         */
        virtual void draw(sf::RenderWindow &window);
        /**
         * @brief  Updates the game over state.
         * 
         * @param dt 
         * @return true 
         * @return false 
         */
        virtual bool update(sf::Time dt);
        /**
         * @brief  Handles the game over state's input.
         * 
         * @param event 
         * @param window 
         * @return true 
         * @return false 
         */
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        /**
         * @brief  Handles the game over state's realtime input.
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
        /**
         * @brief  Activates the game over state.
         * 
         */
        void onActivate();

    private:
        Context* mContext;
        sf::RectangleShape backgroundShape;
        sf::Text mGameOverText;
        sf::Text mInstructionText;
        TextFormater mTextFormater;

};
#endif

