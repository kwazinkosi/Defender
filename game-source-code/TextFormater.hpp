#ifndef TEXTFORMATER_HPP
#define TEXTFORMATER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
/**
 * @brief 
 * 
 */
/**
 * @brief The TextFormater class is responsible for formatting text in a specific way.
 * 
 */
class TextFormater{ 

    public:
        /**
         * @brief Construct a new TextFormater object
         * 
         */
        TextFormater();
        /**
         * @brief Destroy the TextFormater object
         * 
         */
        ~TextFormater();
        /**
         * @brief Formats the given text with the specified parameters.
         * 
         * @param text The text to format.
         * @param position The position of the text.
         * @param color The color of the text.
         * @param style The style of the text.
         * @param size The size of the text.
         * @return sf::Text The formatted text.
         */
        sf::Text formatText(const std::string &text, const sf::Vector2f &position, const sf::Color &color, sf::Text::Style, const unsigned int &size);
        /**
         * @brief Draws the text on the given window.
         * 
         * @param window The window to draw the text on.
         */
        void drawText(sf::RenderWindow &window);
        /**
         * @brief Sets the font of the text.
         * 
         * @param fontPath The path to the font file.
         */
        void setFont(const std::string &fontPath);
        /**
         * @brief Sets the string of the text.
         * 
         * @param text The string to set.
         */
        void setString(const std::string &text);
        /**
         * @brief Sets the position of the text.
         * 
         * @param position The position to set.
         */
        void setPosition(const sf::Vector2f &position);
        /**
         * @brief Centers the origin of the text.
         * 
         * @param text The text to center the origin of.
         */
        void centerOrigin(sf::Text &text);
        /**
         * @brief Sets the fill color of the text.
         * 
         * @param color The color to set.
         */
        void setFillColor(const sf::Color &color);
        /**
         * @brief Sets the style of the text.
         * 
         * @param style The style to set.
         */
        void setStyle(sf::Text::Style style);
        /**
         * @brief Sets the character size of the text.
         * 
         * @param size The size to set.
         */
        void setCharacterSize(const unsigned int &size);
        /**
         * @brief Sets the outline color of the text.
         * 
         * @param color The color to set.
         */
        void setOutlineColor(const sf::Color &color);
        /**
         * @brief Sets the outline thickness of the text.
         * 
         * @param thickness The thickness to set.
         */
        void setOutlineThickness(const float &thickness);
        /**
         * @brief Sets the letter spacing of the text.
         * 
         * @param spacing The spacing to set.
         */
        void setLetterSpacing(const float &spacing);
    private:
        sf::Text mText; /**< The text object. */
        sf::Font mFont; /**< The font object. */
};
#endif // TEXTFORMATER_HPP