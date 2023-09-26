#ifndef LANDER_H
#define LANDER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Animation.hpp"
#include "Context.hpp" 
#include "Utills.hpp" 
#include "Projectile.hpp"
#include "Entity.hpp"
#include "CommandQueue.hpp"
#include "Context.hpp"

class Lander : public Entity
{
    public:
        Lander(Context& context);
        virtual ~Lander();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target);
        void update(sf::Time deltaTime, sf::Vector2f targetPosition);

};
#endif

