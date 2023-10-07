#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "State.hpp"
#include "TextFormater.hpp"
#include "StateStack.hpp"

enum class MenuOptions
{
   Play, Help, ScoreState, Options, Exit
};
class MainMenuState : public State
{
    public:
        MainMenuState(StateStack &stack, Context &context);

        virtual void draw(sf::RenderWindow &window);
        virtual bool update(sf::Time dt);   
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        virtual void handleRealtimeInput(sf::RenderWindow &window);
        virtual std::string getStateID() const;
        
        void setupMenuOptions(); //To fill the menu options vector
        void updateOptionText(); //To update the text of the menu options
        void drawMenuOptions(sf::RenderWindow &window); //To draw the menu options

    private:
        TextFormater mTextFormater; //To format the text of the menu options
        sf::Sprite mBackgroundSprite;
        sf::Text mText;
        std::vector<sf::Text> mMenuOptions; //To store the menu options
        std::vector<sf::Text>::iterator mMenuOptionsIterator; 
};

#endif // MAINMENUSTATE_HPP
