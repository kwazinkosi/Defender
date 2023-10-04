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
        explicit Entity(int health, float movementSpeed, sf::Vector2f position, ENTITYTYPE entityType); 
        ~Entity();

        // // Functions
        virtual void update(sf::Time deltaTime)=0;
        virtual void draw(sf::RenderTarget& target)=0;
        virtual ENTITYTYPE getEntityType() const = 0; 
        // Method called when a collision occurs with another collidable object
        virtual void onCollision() = 0;
        bool collisionCheck(Entity* other);
        sf::Vector2f getCenter() const;
        void move(float x, float y);
        void setPosition(sf::Vector2f position);
        void setPosition(float x, float y);
        sf::Vector2f getPosition() const;
        sf::FloatRect getBounds() const;
        sf::Sprite& getSprite();
        void OnDestroy();
        bool isDestroyed() const;
        void setHealth(int health);
        int getHealth() const;
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
