#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Animation
{
    public:
        Animation();
        ~Animation();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target);

    private:
        sf::Sprite mSprite;
        sf::Vector2i mFrameStart;
        sf::Vector2i mFrameSize;
        std::size_t mNumFrames;
        std::size_t mCurrentFrame;
        sf::Time mDuration;  // How long the animation lasts
        sf::Time mElapsedTime;
        sf::Vector2f mPosition;
        bool mRepeat;

};
#endif