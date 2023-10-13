#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <iostream>
#include <cmath>
#include "Entity.hpp"

/**
 * @brief  The type of projectile.
 * 
 */
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
        /**
         * @brief Construct a new Projectile object
         * 
         * @param position 
         * @param direction 
         * @param movementSpeed 
         * @param type 
         */
        Projectile(sf::Vector2f position, sf::Vector2f direction, float movementSpeed, ProjectileType type);
        /**
         * @brief Destroy the Projectile object
         * 
         */
        ~Projectile();

        /**
         * @brief  Initializes the projectile.
         * 
         */
        void initProjectile();
        /**
         * @brief  Updates the projectile's state.
         * 
         * @param deltaTime 
         */
        void update(sf::Time deltaTime);
        /**
         * @brief  Draws the projectile to the screen.
         * 
         * @param target 
         */
        void draw(sf::RenderTarget& target); 
        /**
         * @brief Get the Entity Type object
         * 
         * @return ENTITYTYPE 
         */
        ENTITYTYPE getEntityType() const; 
        /**
         * @brief  checks for collisions with other entities.
         * 
         */
        void onCollision();
        /**
         * @brief  Destroys the projectile.
         * 
         */
        void onDestroy();
        /**
         * @brief  Returns true if the projectile is destroyed.
         * 
         * @return true 
         * @return false 
         */
        bool isDestroyed() const;
       /**
        * @brief  aiming the projectile at a target.
        * 
        * @param targetPosition 
        */
        void aim(sf::Vector2f targetPosition);
        /**
         * @brief Set the Movement Speed object
         * 
         * @param movementSpeed 
         */
        void setMovementSpeed(float movementSpeed);
        /**
         * @brief Set the Projectile Type object
         * 
         * @param projectileType 
         */
        void setProjectileType(ProjectileType projectileType);
        /**
         * @brief Get the Sprite object
         * 
         * @return sf::Sprite& 
         */
        sf::Sprite &getSprite();
        /**
         * @brief Get the Bounds object
         * 
         * @return sf::FloatRect 
         */
        sf::FloatRect getBounds() const;
        /**
         * @brief Get the Projectile Type object
         * 
         * @return ProjectileType 
         */
        ProjectileType getProjectileType() const;
        /**
         * @brief  Returns true if the projectile is guided.
         * 
         * @return true 
         * @return false 
         */
        bool isGuided() const; // Returns true if the projectile is guided.

    private:
        void updateCurrent(sf::Time deltaTime); // Updates the projectile's state.-+
        void drawCurrent(sf::RenderTarget& target);
        // Objects
        // Variables
        ProjectileType mProjectileType;
        sf::Vector2f mProjectileDirection; // The direction the projectile is moving in.    
};

#endif // PROJECTILE_HPP