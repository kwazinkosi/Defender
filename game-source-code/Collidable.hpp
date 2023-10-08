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

    /**
     * @brief Get the Bounding Box object
     * 
     * @return sf::FloatRect 
     */
    virtual sf::FloatRect getBoundingBox() const = 0;

    /**
     * @brief Get the Position object
     * 
     * @return sf::Vector2f 
     */
    virtual sf::Vector2f getPosition() const = 0;

    /**
     * @brief Get the Collision Type object
     * 
     * @return std::string 
     */
    virtual std::string getCollisionType() const = 0;

    /**
     * @brief Get the Collision Response object
     * 
     * @return std::string 
     */
    virtual void onCollision(Collidable* other) = 0;

    /**
     * @brief Get the Collision Response object
     * 
     * @return std::string 
     */
    virtual bool isStatic() const = 0;

    /**
     * @brief Get the Collision Response object
     * 
     * @return std::string 
     */
    virtual std::string getCollisionResponse() const = 0;
};

#endif // COLLIDABLE_HPP
