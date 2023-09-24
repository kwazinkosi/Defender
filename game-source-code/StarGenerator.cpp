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
    for (auto i = 0; i < staNum; ++i)
    {
        // Generate random spectral type
        StarSpectralType spectralType = static_cast<StarSpectralType>(rand() % static_cast<int>(StarSpectralType::StarSpectralTypeCount));
        // Generate star of random spectral type
        Star star = generateStar(spectralType);
        // Add star to vector
        mStars.push_back(star);
    }
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
    // Generate random size
    sf::CircleShape cSize;
    cSize.setRadius(mass);
    return cSize;
}

sf::Vector2f StarGenerator::generateStarPosition()
{
    auto groundHieght = 10.f;
    auto mountainHieght = 128.f;
    auto skyHieght = mWorldView->getSize().y - groundHieght - mountainHieght; // == skyPos
    sf::Vector2f position;
    position.x = rand() %800;
    position.y = rand() % int(skyHieght); // y position is between 0 and 1/3 of the screen
    return position;
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


