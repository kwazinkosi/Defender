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
    auto removeStarIndex = std::vector<int>();
    // Move stars
    if (mStars.empty())
    {
        throw std::runtime_error("No stars to move!");
        return;
    }

    for (auto i = 0u; i < mStars.size(); ++i)
    {
        // Get star position
        sf::Vector2f position = mStars[i].position;
        // Get star velocity
        sf::Vector2f velocity = mStars[i].velocity;
        // Move star
        position += velocity * deltaTime.asSeconds();
        // Set star position
        mStars[i].position = position;
        // Update star lifetime
        mStars[i].lifetime -= deltaTime;
        // Remove star if lifetime is 0
        if ((mStars[i].lifetime <= sf::Time::Zero) || (mStars[i].position.x < 0 || mStars[i].position.y < -800.f) ||
            (mStars[i].position.x > 2336.f || mStars[i].position.y > mTarget.getSize().y - 30.f))
        {
            // std::cout << "StarGenerator::moveStars() - Removing star at " << mStars[i].position.x << " | " << mStars[i].position.y << " with velocity " << mStars[i].velocity.x << " | " << mStars[i].velocity.y << " and lifetime " << mStars[i].lifetime.asSeconds() << std::endl;
            removeStarIndex.push_back(i);
        }
    }
    // Remove stars
    for (auto i = 0u; i < removeStarIndex.size() && !removeStarIndex.empty(); ++i)
    {
        mStars.erase(mStars.begin() + removeStarIndex[i]);
    }
    // shrink stars vector
    mStars.shrink_to_fit(); // shrink vector to fit number of stars
    removeStarIndex.clear();

    // Generate stars if there are less than 10 stars
    if (int(mStars.size()) < mStarCount - 1)
    {
        auto staNum = mStarCount - mStars.size();
        generateStars(staNum);
    }
}


sf::Color StarGenerator::generateStarColor(StarSpectralType spectralType)
{
    // Generate random color
    sf::Color color;
    switch (spectralType)
    {
    case StarSpectralType::O:
        color = sf::Color(155, 176, 255); // blue-white
        break;
    case StarSpectralType::B:
        color = sf::Color(170, 193, 255); // blue
        break;
    case StarSpectralType::A:
        color = sf::Color(193, 205, 255); // blue-white
        break;
    case StarSpectralType::F:
        color = sf::Color(226, 232, 255); // blue-white
        break;
    case StarSpectralType::G:
        color = sf::Color(255, 255, 255); // white
        break;
    case StarSpectralType::K:
        color = sf::Color(245, 224, 178); // orange
        break;
    case StarSpectralType::M:
        color = sf::Color(240, 110, 110); // red
        break;
    default:
        color = sf::Color(255, 255, 255); // default to white
        break;
    }
    return color;
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
    // Generate random velocity
    int randNumx = rand() % 5;
    int randNumy = rand() % 5;
    sf::Vector2f velocity;
    if (randNumx == 1)
    {
        velocity.x = float(rand() % 50 + 50) * -1.f;
    }
    else if (randNumx == 0)
    {
        velocity.x = float(rand() % 50 + 50);
    }
    else
    {
        velocity.x = 25.f;
    }

    if (randNumy == 1)
    {
        velocity.y = float(rand() % 10 + 10) * -1.f;
    }
    else if (randNumy == 0)
    {
        velocity.y = float(rand() % 10 + 10);
    }
    else
    {
        velocity.y = 0;
        velocity.x = 0;
    }

    return velocity;
}

void StarGenerator::draw(sf::RenderTarget &target)
{
    if (mStars.empty())
    {
        throw std::runtime_error("No stars to draw!");
    }
    // Draw stars

    for (auto &star : mStars)
    {
        // Set star color
        star.size.setFillColor(star.color);
        // Set star position
        star.size.setPosition(star.position);
        // Draw star
        target.draw(star.size);
    }
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


