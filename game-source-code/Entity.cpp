#include "Entity.hpp"

Entity::Entity(int health, float movementSpeed, sf::Vector2f position, ENTITYTYPE entityType)
: mAnimation(nullptr)
, mPosition(position)
, mEntityType(entityType)
, mMovementSpeed(movementSpeed)
, mDestroyed(false)  
, mHealth(health)
  
{
}

Entity::~Entity()
{
    
}

void Entity::move(float x, float y)
{
   sprite.move(x, y);
}

void Entity::OnDestroy()
{
    mDestroyed = true;
}

void Entity::changeAnimation(sf::Vector2f position, sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat)
{
    mAnimation = std::make_unique<Animation>(&texture, position, frameStart, frameSize, numFrames, duration, repeat);
}

bool Entity::isDestroyed() const
{
    return mDestroyed;
}

void Entity::setHealth(int health)
{
    mHealth = health;
}

void Entity::setCollisionType(CollisionType collisionType)
{
    mCollisionType = collisionType;
}

void Entity::setPosition(sf::Vector2f position)
{
    mPosition = position;
}

void Entity::setMovementSpeed(float movementSpeed)
{
    mMovementSpeed = movementSpeed;
}

int Entity::getHealth() const
{
    return mHealth;
}

float Entity::getSpeed() const
{
    return mMovementSpeed;
}

int Entity::getCollisionMask() const
{
    return static_cast<int>(mCollisionType);
}
sf::FloatRect Entity::getBounds() const
{
    return sprite.getGlobalBounds();
}

sf::Sprite &Entity::getSprite()
{
    return sprite;
}

sf::Vector2f Entity::getPosition() const
{
    return mPosition;
}
