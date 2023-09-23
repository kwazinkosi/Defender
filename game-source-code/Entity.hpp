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


// Bitwise enum for colliidable objects
enum class CollisionType
{
    None = 0,
    Player = 1 << 0,
    Enemy = 1 << 1,
    Projectile = 1 << 2,
    MineBomb = 1 << 3,
    PowerUp = 1 << 4,
    Collidable = 1 << 5,
    Asteroid = 1 << 6,
    Humanoid = 1 << 7,
};
// This is the base class for all entities (player, enemy, etc.) in the game, it contains all the common variables and functions that all entities will use
class Entity
{
    public:
        explicit Entity(int health, float movementSpeed, sf::Vector2f position, ENTITYTYPE entityType); 
        ~Entity();

        // Functions
        virtual void update(sf::Time deltaTime) = 0;
        virtual void draw(sf::RenderTarget& target) = 0;
        // Check if the collidable object is static( does not move)
        virtual bool isStatic() const = 0;
        virtual ENTITYTYPE getEntityType() const = 0; 
        // Method called when a collision occurs with another collidable object
        virtual void onCollision() = 0;
        virtual bool collissionCheck(Entity* other) = 0;
        void move(float x, float y);
        // method called when the entity is destroyed
        virtual void OnDestroy();
        // Change the animation of the entity to the specified animation
        void changeAnimation(sf::Vector2f position, sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat);
        

        // Getters and setters
        bool isDestroyed() const;
        void setHealth(int health);
        void setCollisionType(CollisionType collisionType);
        void setPosition(sf::Vector2f position);
        void setMovementSpeed(float movementSpeed);
        int getHealth() const;
        float getSpeed() const;
        int getCollisionMask() const;
        sf::FloatRect getBounds() const;
        sf::Sprite& getSprite();
        sf::Vector2f getPosition() const;
        
    protected:
        // Objects
        CollisionType mCollisionType;
        std::unique_ptr<Animation> mAnimation;
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
