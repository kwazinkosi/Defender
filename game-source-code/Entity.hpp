#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <iostream>
#include "Animation.hpp"
#include "Utills.hpp"


// This is the base class for all entities (player, enemy, etc.) in the game, it contains all the common variables and functions that all entities will use
class Entity
{
    public:
        /**
         * @brief Construct a new Entity object 
         * 
         * @param health 
         * @param movementSpeed 
         * @param position 
         * @param entityType 
         */
        explicit Entity(int health, float movementSpeed, sf::Vector2f position, ENTITYTYPE entityType); 
        /**
         * @brief Destroy the Entity object
         * 
         */
        ~Entity();

        /**
         * @brief  Updates the entity's state.
         * 
         * @param deltaTime 
         */
        virtual void update(sf::Time deltaTime)=0;
        /**
         * @brief  Draws the entity to the screen.
         * 
         * @param target 
         */
        virtual void draw(sf::RenderTarget& target)=0;
        /**
         * @brief Get the Entity Type object 
         * 
         * @return ENTITYTYPE 
         */
        virtual ENTITYTYPE getEntityType() const = 0; 
        /**
         * @brief  checks for collision with another entity.
         * 
         */
        virtual void onCollision() = 0;
        /**
         * @brief  sets collioion check with another entity.
         * 
         * @param other 
         * @return true 
         * @return false 
         */
        bool collisionCheck(Entity* other);
        /**
         * @brief Get the Center object
         * 
         * @return sf::Vector2f 
         */
        sf::Vector2f getCenter() const;
        /**
         * @brief  Moves the entity.
         * 
         * @param x 
         * @param y 
         */
        void move(float x, float y);
        /**
         * @brief Set the Position object 
         * 
         * @param position 
         */
        void setPosition(sf::Vector2f position);
        /**
         * @brief Set the Position object 
         * 
         * @param x 
         * @param y 
         */
        void setPosition(float x, float y);
        /**
         * @brief Get the Position object
         * 
         * @return sf::Vector2f 
         */
        sf::Vector2f getPosition() const;
        /**
         * @brief Get the Bounds object 
         * 
         * @return sf::FloatRect 
         */
        sf::FloatRect getBounds() const;
        /**
         * @brief Get the Sprite object
         * 
         * @return sf::Sprite& 
         */
        sf::Sprite& getSprite();
        /**
         * @brief  Destroys the entity.
         * 
         */
        void OnDestroy();
        /**
         * @brief  Returns true if the entity is destroyed.
         * 
         * @return true 
         * @return false 
         */
        bool isDestroyed() const;
        /**
         *  @brief  Sets the health of the entity.
         *  @param health
        */
        void setHealth(int health);
        /**
         * @brief Get the Health object
         * 
         * @return int 
         */
        int getHealth() const;
        /**
         * @brief Set the Movement Speed object
         * 
         * @param movementSpeed 
         */
        void setMovementSpeed(float movementSpeed);

    protected:
        // Objects
        // Variables
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f mPosition;
        ENTITYTYPE mEntityType;
        float mMovementSpeed;
        bool mDestroyed;
    private:
        // Variables
        int mHealth;
};
#endif // ENTITY_HPP
