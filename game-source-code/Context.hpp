#ifndef Context_HPP
#define Context_HPP

#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>

class Context
{
    public:
        Context();
        ~Context();

        sf::RenderWindow mWindow;
};
#endif // Context_HPP
