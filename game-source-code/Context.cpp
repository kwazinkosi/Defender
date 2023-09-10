#include "Context.hpp"

Context::Context() : mWindow(sf::VideoMode(800, 600), "Defender Shooter", sf::Style::Close)
{

}

Context::~Context()
{
    // dtor
}