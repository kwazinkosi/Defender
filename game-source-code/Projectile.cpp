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
    if (mProjectileType == ProjectileType::PlayerBullet)
    {
        if (!texture.loadFromFile("resources/textures/01.png"))
        {
            throw "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file.";
        }
        // initialize the collidables vector
        mCollisionType = CollisionType::Projectile;
    }
    else if (mProjectileType == ProjectileType::EnemyBullet)
    {
        if (!texture.loadFromFile("resources/textures/02.png"))
        {
            throw "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file.";
        }
        // initialize the collidables vector
        mCollisionType = CollisionType::Projectile;
    }
    else if (mProjectileType == ProjectileType::Missile)
    {
        if (!texture.loadFromFile("resources/textures/02.png"))
        {
            throw "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file.";
        }
        // initialize the collidables vector
        mCollisionType = CollisionType::Projectile;
    }
    
    sprite.setTexture(texture);
    sprite.setScale(0.3f, 0.2f);
    //std::cout << "Projectile::initProjectile() -- Projectile initialized." << std::endl;
}

void Projectile::aim(sf::Vector2f targetPosition)
{
    sf::Vector2f direction;
    direction.x = targetPosition.x - sprite.getPosition().x;
    direction.y = targetPosition.y - sprite.getPosition().y;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0)
    {
        direction.x /= length;
        direction.y /= length;
    }
    mProjectileDirection = direction;
}
