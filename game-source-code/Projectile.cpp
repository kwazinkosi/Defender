#include "Projectile.hpp"

Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction, float movementSpeed, ProjectileType type)
: Entity (1, movementSpeed, position, ENTITYTYPE::PROJECTILE)
, mProjectileType(ProjectileType::PlayerBullet)
, mProjectileDirection(direction)
{
    
    initProjectile();
    mMovementSpeed = movementSpeed;
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    //std::cout << "Projectile::Projectile() -- Projectile created." << std::endl;
}

Projectile::~Projectile()
{
}

void Projectile::initProjectile()
{
    
}
