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

}

void Entity::OnDestroy()
{
}

void Entity::changeAnimation(sf::Vector2f position, sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat)
{
}

bool Entity::isDestroyed() const
{
    return mDestroyed;
}

void Entity::setHealth(int health)
{
    mHealth = health;
}

void Entity::setSpeed(float speed)
{
    mMovementSpeed = speed;
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
}

float Entity::getSpeed() const
{
}

int Entity::getCollisionMask() const
{
}
sf::FloatRect Entity::getBounds() const
{
}

sf::Sprite &Entity::getSprite()
{
}

sf::Vector2f Entity::getPosition() const
{
}
