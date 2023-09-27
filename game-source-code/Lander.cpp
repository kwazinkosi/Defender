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

void Lander::update(sf::Time deltaTime, sf::Vector2f playerPosition)
{
    // Check if it's time to change direction
    if (mLanderClock.getElapsedTime() - spawnTime >= sf::seconds(7.f))
    {
        // Waited for 7 seconds, change direction randomly
        int randomDirection = rand() % 4; // 0: Up, 1: Down, 2: Left, 3: Right
        switch (randomDirection)
        {
        case 0:
            setState(ENEMYSTATE::MOVINGUP);
            break;
        case 1:
            setState(ENEMYSTATE::MOVINGDOWN);
            break;
        case 2:
            setState(ENEMYSTATE::MOVINGLEFT);
            break;
        case 3:
            setState(ENEMYSTATE::MOVINGRIGHT);
            break;
        default:
            break;
        }
        // Reset spawn time
        spawnTime = mLanderClock.getElapsedTime();
    }
    mTargetPosition = playerPosition;
    sf::Vector2f landerPosition = mLanderSprite.getPosition();
    float distance = std::sqrt(pow(mTargetPosition.x - landerPosition.x, 2) + pow(mTargetPosition.y - landerPosition.y, 2));
    //std::cout<<"distance: " << distance << std::endl;
    updateMissiles(deltaTime);
    if (distance <= 200.f && mMissileTimer.getElapsedTime().asSeconds() >= 5.0f)
    {
        fireMissile();
        mMissileTimer.restart(); 
    }
    // Handle movement based on the current state
    if (enemyState == ENEMYSTATE::MOVINGDOWN)
    {
        moveDown(deltaTime);
    }
    else if (enemyState == ENEMYSTATE::MOVINGUP)
    {
        moveUp(deltaTime);
    }
    else if (enemyState == ENEMYSTATE::MOVINGLEFT)
    {
        moveLeft(deltaTime);
    }
    else if (enemyState == ENEMYSTATE::MOVINGRIGHT)
    {
        moveRight(deltaTime);
    }
    // Check if the Lander is going out of the screen boundaries
    const sf::Vector2f position = mLanderSprite.getPosition();
    if (position.x < mContext->mLeftBound)
    {
        // check if the lander is going out of the left bound
        mLanderSprite.setPosition(mContext->mLeftBound, position.y);
        setState(ENEMYSTATE::MOVINGRIGHT);
    }
    else if (position.x  > mContext->mRightBound - mLanderSprite.getGlobalBounds().width)
    {
        mLanderSprite.setPosition(mContext->mRightBound - mLanderSprite.getGlobalBounds().width, position.y);
        setState(ENEMYSTATE::MOVINGLEFT);
    }
    if (position.y < mContext->mTopBound)
    {
        // check if the lander is going out of the top bound
        mLanderSprite.setPosition(position.x, mContext->mTopBound);
        setState(ENEMYSTATE::MOVINGDOWN);
    }
    else if (position.y > mContext->mBottomBound - mLanderSprite.getGlobalBounds().height)
    {
        mLanderSprite.setPosition(position.x, mContext->mBottomBound - mLanderSprite.getGlobalBounds().height);
        setState(ENEMYSTATE::MOVINGUP);
    }
}

void Lander::initLander()
{
    texture = mContext->mTextures->getResourceById(Textures::Lander);
    std::cout << "size: " << texture.getSize().x/5 << " " << texture.getSize().y << std::endl;
    mLanderSprite.setTextureRect(sf::IntRect(0, 0, 26, 24));
    mLanderSprite.setTexture(texture);
    speed = 100.0f;
    spawnPosition();
}

ENEMYSTATE Lander::getState() const
{
    return enemyState;
}

void Lander::setState(ENEMYSTATE state)
{
    enemyState = state;
}

void Lander::spawnPosition()
{
    auto randX = rand() % int (mContext->mRightBound - mLanderSprite.getGlobalBounds().width);
    auto randY = rand() % int (mContext->mTopBound/4);
    mLanderSprite.setPosition(static_cast<float>(randX), static_cast<float>(randY));
}

bool Lander::isAlive() const
{
    return isActive;
}

std::vector<std::unique_ptr<Projectile>>& Lander::getMissiles()
{
    return mMissiles;
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