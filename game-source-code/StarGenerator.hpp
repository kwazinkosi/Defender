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
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget &target);
        Star generateStar(StarSpectralType spectralType);


    private:
        void generateStars(int staNum);
        void moveStars(sf::Time deltaTime);
        sf::Color generateStarColor(StarSpectralType spectralType);
        sf::CircleShape generateStarSize(float mass);
        sf::Vector2f generateStarPosition();
        sf::Vector2f generateStarVelocity();
        sf::RenderTarget &mTarget; // target to draw stars to
        sf::View *mWorldView; // world view
        std::vector<Star> mStars; // vector of stars
        sf::Time mStarTimer; 
        Star mStar; // star
        int mStarCount; // number of stars


};
#endif