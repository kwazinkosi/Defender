#ifndef HELPSTATE_HPP
#define HELPSTATE_HPP

#include <memory>
#include <fstream>
#include "State.hpp"
#include "TextFormater.hpp"


class HelpState : public State
{
    public:
        HelpState(StateStack& stack, Context &context);
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