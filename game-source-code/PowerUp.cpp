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
}

void PowerUp::draw(sf::RenderTarget& target)
{
    if(!isDestroyed())
        target.draw(sprite);
}


bool PowerUp::isStatic() const
{
    return true;
}

ENTITYTYPE PowerUp::getEntityType() const
{
    return mEntityType;
}

bool PowerUp::collissionCheck(Entity* other)
{
    if(other->getEntityType() == ENTITYTYPE::PLAYER)
    {
        return getBounds().intersects(other->getBounds());
    }
    return false;
}

void PowerUp::onCollision()
{
}

void PowerUp::onDestroy()
{
    mDestroyed = true;
}

bool PowerUp::isDestroyed() const
{
    return mDestroyed;
}

sf::Vector2f PowerUp::spawnPosition()
{
    sf::Vector2f position;
    position.x = rand() % int(mContext->mRightBound - 34.f);
    position.y = mContext->mBottomBound - 34.f;
    return position;
}
