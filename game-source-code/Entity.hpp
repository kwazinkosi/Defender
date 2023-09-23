#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <iostream>
#include "Utills.hpp"

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
        
    private:
        // Variables
        int mHealth;
};

#endif // ENTITY_HPP
