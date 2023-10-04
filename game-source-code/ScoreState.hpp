#ifndef SCORESTATE_HPP
#define SCORESTATE_HPP

#include <memory>
#include <fstream>
#include "State.hpp"
#include "TextFormater.hpp"

class ScoreState : public State
{
    public:
        ScoreState(StateStack& stack, Context &context);
        virtual void draw(sf::RenderWindow &window);
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event &event, sf::RenderWindow &window);
        virtual void handleRealtimeInput(sf::RenderWindow &window);
        virtual std::string getStateID() const;
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