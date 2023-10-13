#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "State.hpp"
#include "TextFormater.hpp"

class PauseState : public State
{
    public:
    /**
     * @brief Construct a new Pause State object
     * 
     * @param stack 
     * @param context 
     */
        PauseState(StateStack& stack, Context &context);
        /**
         * @brief  draws the pause state to the screen.
         * 
         * @param window 
         */
        virtual void draw(sf::RenderWindow &window);
        /**
         * @brief  Updates the pause state.
         * 
         * @param dt 
         * @return true 
         * @return false 
         */
        virtual bool update(sf::Time dt);
        /**
         * @brief  Handles the pause state's input.
         * 
         * @param event 
         * @param window 
         * @return true 
         * @return false 
         */
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        /**
         * @brief  Handles the pause state's realtime input.
         * 
         * @param window 
         */
        virtual void handleRealtimeInput(sf::RenderWindow &window) ;
        /**
         * @brief Get the State I D object
         * 
         * @return std::string 
         */
        virtual std::string getStateID() const;
        
    private:
        sf::RectangleShape backgroundShape;
        sf::Text mPausedText;
        sf::Text mInstructionText;
        TextFormater mTextFormater;
};
#endif // PAUSESTATE_HPP
