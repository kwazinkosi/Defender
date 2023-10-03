#include "Asteroid.hpp"
#include <cmath>

Asteroid::Asteroid(Context &context, sf::Vector2f position)
    : Entity(100, 0.f, position, ENTITYTYPE::ASTEROID), mContext(&context)
{
    initAsteroid();
    std::cout << "Asteroid::Asteroid() -- Asteroid created." << std::endl;
}

Asteroid::~Asteroid()
{
}

void Asteroid::initAsteroid()
{
    if (!texture.loadFromFile("resources/textures/Asteroids.png"))
    {
        throw "ERROR::ASTEROID::INITTEXTURE::Could not load texture file.";
    }

    mData = getData();
    sprite.setTexture(texture);
    sprite.setPosition(mData.position);
    sprite.setScale(0.5f, 0.5f);
    setCollisionType(CollisionType::Asteroid);
}
void Asteroid::update(sf::Time deltaTime)
{
    static auto timeToSpawn = sf::seconds(rand() % 4 + 2);
    if ( mData.spawnTime <= sf::Time::Zero|| mAsteroidClock.getElapsedTime().asSeconds() > timeToSpawn.asSeconds())
    {
        mData.spawnTime = sf::Time::Zero;
        moveDown(deltaTime);
        // check if Asteriod is out of bottom of screen
        if (sprite.getPosition().y > mContext->mWorldView.getCenter().y + mContext->mWorldView.getSize().y / 2.f)
        {
            onDestroy();
        }
    }
    onCollision();
    // call the move function

    if (isDestroyed())
    {
        // destroy the Asteroid
        mData.spawnTime -= deltaTime;
        std::cout << "Asteroid::update() -- Asteroid destroyed." << std::endl;
    }
}
