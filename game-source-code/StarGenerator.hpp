#ifndef STAR_GENERATOR_HPP
#define STAR_GENERATOR_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <time.h>
#include <iostream>
#include <memory>
#include <random>
#include "Context.hpp"

enum class StarSpectralType
{
    O,
    B,
    A,
    F,
    G,
    K,
    M,
    StarSpectralTypeCount
};
struct Star
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape size;
    sf::Color color;
    float mass;
    sf::Time lifetime;
};

class StarGenerator
{
    public:
        explicit StarGenerator(Context &context);


    private:


};
#endif