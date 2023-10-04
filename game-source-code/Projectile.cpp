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
    }
    else if (mProjectileType == ProjectileType::EnemyBullet)
    {
        if (!texture.loadFromFile("resources/textures/02.png"))
        {
            throw "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file.";
        }
        // initialize the collidables vector
    }
    else if (mProjectileType == ProjectileType::Missile)
    {
        if (!texture.loadFromFile("resources/textures/02.png"))
        {
            throw "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file.";
        }
        // initialize the collidables vector
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


void Projectile::update(sf::Time deltaTime)
{
    // Move the projectile.
    sprite.move(mProjectileDirection * mMovementSpeed * deltaTime.asSeconds()); // Move the projectile to
}

void Projectile::draw(sf::RenderTarget& target)
{
    target.draw(sprite);
    //std::cout << "Projectile::draw() -- Projectile drawn." << std::endl;
}

ENTITYTYPE Projectile::getEntityType() const
{
    return ENTITYTYPE::PROJECTILE;
}

void Projectile::onCollision()
{

}

void Projectile::onDestroy()
{
    mDestroyed = true;
}

void Projectile::setMovementSpeed(float movementSpeed)
{
    mMovementSpeed = movementSpeed;
}

void Projectile::setProjectileType(ProjectileType projectileType)
{
    mProjectileType = projectileType;
}

bool Projectile::isDestroyed() const
{
    return mDestroyed;
}

sf::Sprite &Projectile::getSprite()
{
    return sprite;
}

sf::FloatRect Projectile::getBounds() const
{
    return sprite.getGlobalBounds();
}

ProjectileType Projectile::getProjectileType() const
{
    return mProjectileType;
}

bool Projectile::isGuided() const
{
    if (mProjectileType == ProjectileType::Missile)
    {
        return true;
    }
    return false;
}

void Projectile::updateCurrent(sf::Time deltaTime)
{
    update(deltaTime);
}

void Projectile::drawCurrent(sf::RenderTarget& target)
{
    draw(target);
}