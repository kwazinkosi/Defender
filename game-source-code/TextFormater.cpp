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

void TextFormater::setFont(const std::string &fontPath)
{
    if (!mFont.loadFromFile(fontPath))
    {
        throw std::runtime_error("Font not found");
    }

    mText.setFont(mFont);

}

void TextFormater::setString(const std::string &text)
{
    mText.setString(text);
}

void TextFormater::setPosition(const sf::Vector2f &position)
{
    mText.setPosition(position);
}

void TextFormater::centerOrigin(sf::Text &text)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);

}

void TextFormater::setFillColor(const sf::Color &color)
{
    mText.setFillColor(color);
}

void TextFormater::setStyle(sf::Text::Style style)
{
    mText.setStyle(style);
}

void TextFormater::setCharacterSize(const unsigned int &size)
{
    mText.setCharacterSize(size);
}

void TextFormater::setOutlineColor(const sf::Color &color)
{
    mText.setOutlineColor(color);
}

void TextFormater::setOutlineThickness(const float &thickness)
{
    mText.setOutlineThickness(thickness);
}

void TextFormater::setLetterSpacing(const float &spacingFactor)
{
    mText.setLetterSpacing(spacingFactor);
}


