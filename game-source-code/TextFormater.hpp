#ifndef TEXTFORMATER_HPP
#define TEXTFORMATER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

class TextFormater{ 

    public:
        TextFormater();
        ~TextFormater();
        sf::Text formatText(const std::string &text, const sf::Vector2f &position, const sf::Color &color, sf::Text::Style, const unsigned int &size);
        void drawText(sf::RenderWindow &window);
       
    private:
        sf::Text mText;
        sf::Font mFont;
};
#endif // TEXTFORMATER_HPP