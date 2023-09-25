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
        PowerUp(Context &context, sf::Vector2f position);
        ~PowerUp();
        void initPowerUp();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target); 
        bool isStatic() const;
        ENTITYTYPE getEntityType() const; 
        bool collissionCheck(Entity* other);
        void onCollision();id onDestroy();
        bool isDestroyed() const;

    private:
        Context *mContext;
        sf::Clock mPowerUpClock;
        sf::Time mPowerUpTime;
        float mLifeTime;
        sf::Vector2f spawnPosition();

};
#endif