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

    private:
        Context *mContext;

};
#endif