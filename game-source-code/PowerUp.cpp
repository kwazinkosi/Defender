#include "PowerUp.hpp"

PowerUp::PowerUp(Context &context, sf::Vector2f position)
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::initPowerUp()
{
}

void PowerUp::update(sf::Time deltaTime)
{
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

bool PowerUp::isDestroyed() const
{
    return false;
}

sf::Vector2f PowerUp::spawnPosition()
{
    return sf::Vector2f();
}
