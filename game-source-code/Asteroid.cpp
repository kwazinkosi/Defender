#include "Asteroid.hpp"
#include <cmath>

Asteroid::Asteroid(Context &context, sf::Vector2f position)
    : Entity(100, 0.f, position, ENTITYTYPE::ASTEROID), mContext(&context)
{
    initAsteroid();
    std::cout << "Asteroid::Asteroid() -- Asteroid created." << std::endl;
}

Asteroid::~Asteroid()
{
}

void Asteroid::initAsteroid()
{
    if (!texture.loadFromFile("resources/textures/Asteroids.png"))
    {
        throw "ERROR::ASTEROID::INITTEXTURE::Could not load texture file.";
    }

    mData = getData();
    sprite.setTexture(texture);
    sprite.setPosition(mData.position);
    sprite.setScale(0.5f, 0.5f);
    //setCollisionType(CollisionType::Asteroid);
}
void Asteroid::update(sf::Time deltaTime)
{
    static auto timeToSpawn = sf::seconds(rand() % 4 + 2);
    if ( mData.spawnTime <= sf::Time::Zero|| mAsteroidClock.getElapsedTime().asSeconds() > timeToSpawn.asSeconds())
    {
        mData.spawnTime = sf::Time::Zero;
        moveDown(deltaTime);
        // check if Asteriod is out of bottom of screen
        if (sprite.getPosition().y > mContext->mWorldView.getCenter().y + mContext->mWorldView.getSize().y / 2.f)
        {
            onDestroy();
        }
    }
    onCollision();
    // call the move function

    if (isDestroyed())
    {
        // destroy the Asteroid
        mData.spawnTime -= deltaTime;
        std::cout << "Asteroid::update() -- Asteroid destroyed." << std::endl;
    }
}

void Asteroid::draw(sf::RenderTarget &target)
{
    target.draw(sprite);
}

bool Asteroid::isStatic() const
{
    return false;
}

ENTITYTYPE Asteroid::getEntityType() const
{
    return ENTITYTYPE::ASTEROID;
}

bool Asteroid::collissionCheck(Entity *other)
{
    return getBounds().intersects(other->getBounds()); // Check if the Asteroid collides with the other entity.
}

void Asteroid::onCollision()
{
}

void Asteroid::onDestroy()
{
    mDestroyed = true;
}

bool Asteroid::isDestroyed() const
{
    return mDestroyed;
}

AsteroidData Asteroid::getData()
{
    AsteroidData data;
    data.position = spawnPosition();
    data.velocity = generateAstroidVelocity();
    data.spawnTime = sf::seconds(float(rand() % 3 + 2));
    data.sprite = generateAstroidSize((rand() % 4 + 1) / 2.f);
    return data;
}

void Asteroid::setData(AsteroidData data)
{
    mData = data;
}

sf::Vector2f Asteroid::spawnPosition()
{
    sf::Vector2f position;
    position.x = (rand() % int(mContext->mWorldView.getSize().x/5.f))*5.f - 50.f;
    position.y = ((mContext->mWorldView.getCenter().y - mContext->mWorldView.getSize().y / 2.f) - 100.f);
    if (position.x < 50.f)
    {
        position.x = 50.f;
    }
    if (position.x > mContext->mWorldView.getSize().x - 50.f)
    {
        position.x = mContext->mWorldView.getSize().x - 50.f;
    }
    return position;
}

sf::Sprite Asteroid::generateAstroidSize(float scale)
{
    sf::Sprite sprite;
    sprite.setScale(scale, scale);
    return sprite;
}

sf::Vector2f Asteroid::generateAstroidVelocity()
{
    // Generate random velocity
    int randNumx = rand() % 5;
    int randNumy = rand() % 5;
    sf::Vector2f velocity;
    if (randNumx == 1)
    {
        velocity.y = float(rand() % 50 + 50) * 1.f;
    }
    else if (randNumy == 0)
    {
        velocity.y = float((rand() % 50)*2 + 50);
    }
    else
    {
        velocity.y = 50.f;
    }

    if (randNumx == 1)
    {
        velocity.x = float(rand() % 10 + 10) * -1.f;
    }
    else if (randNumx == 0)
    {
        velocity.x = float(rand() % 10 + 10);
    }
    else
    {
        velocity.x = 0;
    }

    return velocity;
}

void Asteroid::moveDown(sf::Time deltaTime)
{
    sf::Vector2f position = mData.position;
    // Get star velocity
    sf::Vector2f velocity = mData.velocity;
    // Move star
    position += velocity * deltaTime.asSeconds();
    // Set star position
    mData.position = position;
    sprite.setPosition(mData.position); 

}
