#include "Lander.hpp"

Lander::Lander(Context &context)
: Entity(100, 0.f, sf::Vector2f(0.f, 0.f), ENTITYTYPE::ENEMY)
, mContext(&context)
, enemyState(ENEMYSTATE::MOVINGDOWN)
, speed(50.f)
, canShoot(true)
, isActive(true)
, isDown(true)
{
    std::cout << "Lander::Lander() -- Lander created." << std::endl;
    initLander();
    spawnTime = mLanderClock.getElapsedTime();
    fireTimer = mMissileTimer.getElapsedTime();
}



Lander::~Lander()
{
}

void Lander::moveDown(sf::Time deltaTime)
{
    auto randDirX = rand() % 2;
    auto randSpeedX = (rand() % int(speed)) / 3;
    auto randSpeedY = (rand() % int(speed)) / 2 + speed / 2;

    if (randDirX)
    {
        mLanderSprite.move(randSpeedX * deltaTime.asSeconds(), randSpeedY * deltaTime.asSeconds());
    }
    else
    {
        mLanderSprite.move(-randSpeedX * deltaTime.asSeconds(), randSpeedY * deltaTime.asSeconds());
    }
}

void Lander::moveUp(sf::Time deltaTime)
{
    auto randDirX = rand() % 2;
    auto randSpeedX = (rand() % int(speed) / 3);
    auto randSpeedY = (rand() % int(speed) / 2) + speed / 2;

    if (randDirX)
    {
        mLanderSprite.move(randSpeedX * deltaTime.asSeconds(), -randSpeedY * deltaTime.asSeconds());
    }
    else
    {
        mLanderSprite.move(-randSpeedX * deltaTime.asSeconds(), -randSpeedY * deltaTime.asSeconds());
    }
}

void Lander::moveLeft(sf::Time deltaTime)
{
    mLanderSprite.move(-speed * deltaTime.asSeconds(), 0.f);
}

void Lander::moveRight(sf::Time deltaTime)
{
    mLanderSprite.move(speed * deltaTime.asSeconds(), 0.f);
}

void Lander::draw(sf::RenderTarget &target)
{
    target.draw(mLanderSprite);

    for (auto &missile : mMissiles)
    {
        target.draw(missile->getSprite());
    }
}