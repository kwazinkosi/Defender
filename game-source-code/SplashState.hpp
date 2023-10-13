#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP

#include "State.hpp"
#include "StateStack.hpp"
#include "TextFormater.hpp"

/**
 * @brief  The splash state of the game.
 * 
 */
class SplashState : public State
{
    public:
    /**
     * @brief Construct a new Splash State object
     * 
     * @param stack 
     * @param context 
     */
        SplashState(StateStack &stack, Context &context);

        /**
         * @brief  Draw the splash state.
         * 
         * @param window 
         */
        virtual void draw(sf::RenderWindow &window);
        /**
         * @brief  Update the splash state.
         * 
         * @param dt 
         * @return true 
         * @return false 
         */
        virtual bool update(sf::Time dt);
        /**
         * @brief  Handle an event.
         * 
         * @param event 
         * @param window 
         * @return true 
         * @return false 
         */
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        /**
         * @brief  Handle realtime input.
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
        bool mShowText;
        sf::Sprite mBackgroundSprite;
        //sf::Sprite mKeypadSprite;
        sf::Texture mTexture;
        sf::Text mText;
        sf::Time mElapsedTime;

        TextFormater mTextFormater;
        
};

#endif // SPLASHSTATE_HPP