#ifndef SCORESTATE_HPP
#define SCORESTATE_HPP

#include <memory>
#include <fstream>
#include "State.hpp"
#include "TextFormater.hpp"

/**
 * @brief  The score state of the game.
 * 
 */
class ScoreState : public State
{
    public:
        /**
         * @brief Construct a new Score State object
         * 
         * @param stack 
         * @param context 
         */
        ScoreState(StateStack& stack, Context &context);
        /**
         * @brief  Draw the score state.
         * 
         * @param window 
         */
        virtual void draw(sf::RenderWindow &window);
        /**
         * @brief  Update the score state.
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
        virtual void handleRealtimeInput(sf::RenderWindow &window);
        /**
         * @brief Get the State I D object
         * 
         * @return std::string 
         */
        virtual std::string getStateID() const;
        /**
         * @brief  Called when the state is activated.
         * 
         */
        void onActivate();
    private:
        Context* mContext;
        std::fstream file;
        std::string filePath_;
        std::string mScore;
        std::string getScore();
        void drawScore(sf::RenderWindow &window);
        sf::RectangleShape backgroundShape;
        sf::Text HighScoreText;
        sf::Text mInstructionText;
        TextFormater mTextFormater;
        sf::Font font;
};
#endif // GAMEOVERSTATE_HPP