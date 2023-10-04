#include "Entity.hpp"

Entity::Entity(int health, float movementSpeed, sf::Vector2f position, ENTITYTYPE entityType)
: mPosition(position)
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
    mPosition.x += x;
    mPosition.y += y;
}

void Entity::OnDestroy()
{
    mDestroyed = true;
}

bool Entity::isDestroyed() const
{
    return mDestroyed;
}

void Entity::setHealth(int health)
{
    mHealth = health;
}

void Entity::setPosition(sf::Vector2f position)
{
    sprite.setPosition(position);
    mPosition = position;
}

void Entity::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
    mPosition.x = x;
    mPosition.y = y;
}

void Entity::setMovementSpeed(float movementSpeed)
{
    mMovementSpeed = movementSpeed;
}

int Entity::getHealth() const
{
    return mHealth;
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
    //return mPosition;
    return sprite.getPosition();
}

sf::Vector2f Entity::getCenter() const
{
    return sf::Vector2f(getPosition().x + getBounds().width / 2.f, getPosition().y + getBounds().height / 2.f);
}

bool Entity::collisionCheck(Entity* other)
{
    return getBounds().intersects(other->getBounds());
}