#include "StarGenerator.hpp"

StarGenerator::StarGenerator(Context &context)
{
}
void StarGenerator::update(sf::Time deltaTime)
{
}
void StarGenerator::generateStars(int staNum)
{
}

void StarGenerator::moveStars(sf::Time deltaTime)
{
}

sf::Color StarGenerator::generateStarColor(StarSpectralType spectralType)
{
    return sf::Color();
}

sf::CircleShape StarGenerator::generateStarSize(float mass)
{
    return sf::CircleShape();
}

sf::Vector2f StarGenerator::generateStarPosition()
{
    return sf::Vector2f();
}

sf::Vector2f StarGenerator::generateStarVelocity()
{
    return sf::Vector2f();
}

void StarGenerator::draw(sf::RenderTarget &target)
{
}

Star StarGenerator::generateStar(StarSpectralType spectralType)
{
    return Star();
}


