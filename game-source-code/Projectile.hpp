#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <iostream>
#include <cmath>
//#include "Context.hpp"
#include "Entity.hpp"

enum class ProjectileType
{
    EnemyBullet,
    PlayerBullet,
    Missile,
    Mine,
};

class Projectile: public Entity
{
    public:
        //Projectile(ProjectileType projectileType, Context &context);
        Projectile(sf::Vector2f position, sf::Vector2f direction, float movementSpeed, ProjectileType type);
        ~Projectile();

        // Functions
        void initProjectile();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target); 
        bool isStatic() const;
        ENTITYTYPE getEntityType() const; 
        bool collissionCheck(Entity* other);
        void onCollision();

        void onDestroy();
        bool isDestroyed() const;
        void aim(sf::Vector2f targetPosition);
        void setMovementSpeed(float movementSpeed);
        void setProjectileType(ProjectileType projectileType);
        sf::Sprite &getSprite();
        sf::FloatRect getBounds() const;
        ProjectileType getProjectileType() const;
        bool isGuided() const; // Returns true if the projectile is guided.
    private:
        void updateCurrent(sf::Time deltaTime); // Updates the projectile's state.-+
        //void update(sf::Time deltaTimem, CommandQueue &commandQueue);
        void drawCurrent(sf::RenderTarget& target);
        // Objects
        // Variables
        ProjectileType mProjectileType;
        sf::Vector2f mProjectileDirection; // The direction the projectile is moving in.
        
};

#endif // PROJECTILE_HPP