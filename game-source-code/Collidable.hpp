#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include <SFML/Graphics.hpp>

class Collidable {
public:
    /**
     * @brief Construct a new Collidable object
     * 
     */
    Collidable();
    /**
     * @brief Destroy the Collidable object
     * 
     */
    virtual ~Collidable();

    // Get the bounding box of the collidable object
    virtual sf::FloatRect getBoundingBox() const = 0;

    // Get the position of the collidable object
    virtual sf::Vector2f getPosition() const = 0;

    // Get the collision type of the collidable object
    virtual std::string getCollisionType() const = 0;

    // Method called when a collision occurs with another collidable object
    virtual void onCollision(Collidable* other) = 0;

    // Check if the collidable object is static
    virtual bool isStatic() const = 0;

    // Get the collision response type for the collidable object
    virtual std::string getCollisionResponse() const = 0;
};

#endif // COLLIDABLE_HPP
