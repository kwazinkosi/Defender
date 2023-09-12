#include "TextFormater.hpp"

TextFormater::TextFormater()
{
    if (!mFont.loadFromFile("resources/fonts/SpaceObsessed.ttf"))
    {
        throw std::runtime_error("Font not found");
    }
} 

TextFormater::~TextFormater()
{
    //dtor
}

sf::Text TextFormater::formatText(const std::string &text, const sf::Vector2f &position, const sf::Color &color, sf::Text::Style style, const unsigned int &size)
{
    mText.setFont(mFont);
    mText.setString(text);
    mText.setPosition(position);
    mText.setFillColor(color);
    mText.setStyle(style);
    mText.setCharacterSize(size);

    return mText;
}

void TextFormater::drawText(sf::RenderWindow &window)
{
    window.draw(mText);
}

