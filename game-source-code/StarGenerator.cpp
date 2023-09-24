#include "StarGenerator.hpp"

StarGenerator::StarGenerator(Context &context)
    : mTarget(context.mWindow), mWorldView(&context.mWorldView), mStarTimer(sf::Time::Zero), mStarCount(0)
{
    std::cout << "StarGenerator::StarGenerator() - Generating stars" << std::endl;
    mStarCount = rand() % 25 + 25; // generate random number of stars between 5 and 10
    mStars.reserve(mStarCount);    // reserve space for 10 stars
    // Generate stars
    generateStars(mStarCount);
}

void StarGenerator::update(sf::Time deltaTime)
{
    moveStars(deltaTime);
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
    Star star;
    star.position = generateStarPosition();
    star.velocity = generateStarVelocity();
    star.color = generateStarColor(spectralType);
    star.mass = rand() % 1 + 1;
    star.size = generateStarSize(star.mass);
    star.lifetime = sf::seconds(float(rand() % 20 + 20));
    return star;
}


