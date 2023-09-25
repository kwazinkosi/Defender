#include "Projectile.hpp"

Projectile::Projectile(ProjectileType projectileType, Context &context)
: Entity(1, 100.f, sf::Vector2f(0.f, 0.f), ENTITYTYPE::PROJECTILE)
, mContext(context)
{
    
}

Projectile::~Projectile()
{
}