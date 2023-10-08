#ifndef LOADINGSTATE_HPP
#define LOADINGSTATE_HPP

#include "ResourceManager.hpp"
#include "State.hpp"
#include "ParallelTask.hpp"
#include "StateStack.hpp"

class  LoadingState : public State  
{
    public:
    /**
     * @brief Construct a new Loading State object 
     * 
     * @param stack 
     * @param context 
     */
        LoadingState(StateStack& stack, Context &context);
        /**
         * @brief  Draws the loading state to the screen.
         * 
         * @param window 
         */
        virtual void draw(sf::RenderWindow &window);
        /**
         * @brief  Updates the loading state.
         * 
         * @param dt 
         * @return true 
         * @return false 
         */
        virtual bool update(sf::Time dt);
        /**
         * @brief  Handles the loading state's input.
         * 
         * @param event 
         * @param window 
         * @return true 
         * @return false 
         */
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        /**
         * @brief  Handles the loading state's realtime input.
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
        ParallelTask mLoadingTask; // The task that loads the resources
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