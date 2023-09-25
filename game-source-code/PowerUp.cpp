#include "PowerUp.hpp"

PowerUp::PowerUp(Context &context, sf::Vector2f position)
: Entity(1, 0.f, position, ENTITYTYPE::POWERUP)
, mContext(&context)
, mPowerUpTime(sf::Time::Zero)
, mLifeTime(0.0f)
{
    initPowerUp();
    std::cout << "PowerUp::PowerUp() -- PowerUp created." << std::endl;
}

PowerUp::~PowerUp()
{
}

void PowerUp::initPowerUp()
{
    texture = mContext->mTextures->getResourceById(Textures::PowerUp);
    // smooth the texture
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(spawnPosition());
    mLifeTime = float(rand() % 10) + 10.f;
    sprite.setScale(0.5f, 0.5f);
    setCollisionType(CollisionType::PowerUp);
}

void PowerUp::update(sf::Time deltaTime)
{
    mPowerUpTime += deltaTime;
    if (mPowerUpTime.asSeconds() >= mLifeTime)
    {
        onDestroy();
        mPowerUpTime = sf::Time::Zero;
        mLifeTime = 0.0f;
    }

    onCollision();
    if(isDestroyed())
    {
    }

}

void PowerUp::draw(sf::RenderTarget &target)
{
}

bool PowerUp::isStatic() const
{
    return false;
}

ENTITYTYPE PowerUp::getEntityType() const
{
    return ENTITYTYPE();
}

bool PowerUp::collissionCheck(Entity *other)
{
    return false;
}

void PowerUp::onCollision()
{
}

void PowerUp::onDestroy()
{
}

bool PowerUp::isDestroyed() const
{
    return false;
}

sf::Vector2f PowerUp::spawnPosition()
{
    return sf::Vector2f();
}
