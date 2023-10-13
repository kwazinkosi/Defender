#ifndef HELPSTATE_HPP
#define HELPSTATE_HPP

#include <memory>
#include <fstream>
#include "State.hpp"
#include "TextFormater.hpp"


class HelpState : public State
{
    public:
        /**
         * @brief Construct a new Help State object
         * 
         * @param stack 
         * @param context 
         */
        HelpState(StateStack& stack, Context &context);
        /**
         * @brief  draws the help state to the screen.
         * 
         * @param window 
         */
        virtual void draw(sf::RenderWindow &window);
        /**
         * @brief  Updates the help state.
         * 
         * @param dt 
         * @return true 
         * @return false 
         */
        virtual bool update(sf::Time dt);
        /**
         * @brief  Handles the help state's input.
         * 
         * @param event 
         * @param window 
         * @return true 
         * @return false 
         */
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        /**
         * @brief  Handles the help state's realtime input.
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
         * @brief  Activates the help state.
         * 
         */
        void onActivate();
    private:
        Context* mContext;
        std::fstream file;
        std::string filePath_;
        std::string mHelp;
        void drawHelp(sf::RenderWindow &window);
        sf::RectangleShape backgroundShape;
        sf::Text helpText;
        sf::Text mInstructionText;
        TextFormater mTextFormater;
        sf::Font font;
        sf::Font instructionFont;
};
#endif // GAMEOVERSTATE_HPP