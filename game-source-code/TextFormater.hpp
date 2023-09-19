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
        void setFont(const std::string &fontPath);
        void setString(const std::string &text);
        void setPosition(const sf::Vector2f &position);
        void centerOrigin(sf::Text &text);
        void setFillColor(const sf::Color &color);
        void setStyle(sf::Text::Style style);
        void setCharacterSize(const unsigned int &size);
        void setOutlineColor(const sf::Color &color);
        void setOutlineThickness(const float &thickness);
        void setLetterSpacing(const float &spacing);
    private:
        sf::Text mText;
        sf::Font mFont;
};
#endif // TEXTFORMATER_HPP