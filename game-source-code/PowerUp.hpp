#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include "Entity.hpp"
#include "Context.hpp"
#include "Utills.hpp"


class PowerUp: public Entity
{
    public:
        /**
         * @brief Construct a new Power Up object
         * 
         * @param context 
         * @param position 
         */
        PowerUp(Context &context, sf::Vector2f position);
        /**
         * @brief Destroy the Power Up object
         * 
         */
        ~PowerUp();
        /**
         * @brief   Initializes the power up.
         * 
         */
        void initPowerUp();
        /**
         * @brief  Updates the power up's state.
         * 
         * @param deltaTime 
         */
        void update(sf::Time deltaTime);
        /**
         * @brief  Draws the power up to the screen.
         * 
         * @param target 
         */
        void draw(sf::RenderTarget& target); 
        /**
         * @brief  checks if the power up is static.
         * 
         * @return true 
         * @return false 
         */
        bool isStatic() const;
        /**
         * @brief Get the Entity Type object
         * 
         * @return ENTITYTYPE 
         */
        ENTITYTYPE getEntityType() const; 
        /**
         * @brief  Checks if the power up collides with another entity.
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool collissionCheck(Entity* other);
        /**
         * @brief  checks for collisions with other entities.
         * 
         */
        void onCollision();
        /**
         * @brief  Destroys the power up.
         * 
         */
        void onDestroy();
        /**
         * @brief   Returns true if the power up is destroyed.
         * 
         * @return true 
         * @return false 
         */
        bool isDestroyed() const;

    private:
        Context *mContext;
        sf::Clock mPowerUpClock;
        sf::Time mPowerUpTime;
        float mLifeTime;
        sf::Vector2f spawnPosition();

};
#endif