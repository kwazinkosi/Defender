#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "State.hpp"
#include "TextFormater.hpp"
#include "StateStack.hpp"

/**
 * @brief  The options of the main menu.
 * 
 */
enum class MenuOptions
{
   Play, Help, ScoreState, Options, Exit
};
class MainMenuState : public State
{
    public:
        /**
         * @brief Construct a new Main Menu State object
         * 
         * @param stack 
         * @param context 
         */
        MainMenuState(StateStack &stack, Context &context);
        /**
         * @brief  Draws the main menu state to the screen.
         * 
         * @param window 
         */
        virtual void draw(sf::RenderWindow &window);
        /**
         * @brief  Updates the main menu state.
         * 
         * @param dt 
         * @return true 
         * @return false 
         */
        virtual bool update(sf::Time dt);   
        /**
         * @brief  Handles the main menu state's input.
         * 
         * @param event 
         * @param window 
         * @return true 
         * @return false 
         */
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        /**
         * @brief  Handles the main menu state's realtime input.
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
         * @brief  Sets up the main menu state.
         * 
         */
        void setupMenuOptions(); //To fill the menu options vector
        /**
         * @brief  Updates the text of the menu options.
         * 
         */
        void updateOptionText(); //To update the text of the menu options
        /**
         * @brief  Draws the menu options to the screen.
         * 
         * @param window 
         */
        void drawMenuOptions(sf::RenderWindow &window); //To draw the menu options

    private:
        TextFormater mTextFormater; //To format the text of the menu options
        sf::Sprite mBackgroundSprite;
        sf::Text mText;
        std::vector<sf::Text> mMenuOptions; //To store the menu options
        std::vector<sf::Text>::iterator mMenuOptionsIterator; 
};

#endif // MAINMENUSTATE_HPP
