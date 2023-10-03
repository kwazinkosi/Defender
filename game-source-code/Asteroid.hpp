#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "Entity.hpp"
#include "Context.hpp"
#include "Utills.hpp"
#include "CommandQueue.hpp"

struct AsteroidData
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Sprite sprite;
    sf::Time spawnTime;
};

class Asteroid: public Entity
{
    public:
        Asteroid(Context &context, sf::Vector2f position);
        ~Asteroid();
        void initAsteroid();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target);
        bool isStatic() const;
        ENTITYTYPE getEntityType() const; 
        bool collissionCheck(Entity* other);
        void onCollision();
        void onDestroy();
        bool isDestroyed() const;
        AsteroidData getData();

        void setData(AsteroidData data);
    private:
        sf::Vector2f spawnPosition();
        sf::Sprite generateAstroidSize(float scale);
        sf::Vector2f generateAstroidVelocity();
        void moveDown(sf::Time deltaTime);
        AsteroidData mData;
        Context *mContext;
        sf::Clock mAsteroidClock;
        sf::Time mAsteroidTime;
         
};

#endif // ASTEROID_HPP