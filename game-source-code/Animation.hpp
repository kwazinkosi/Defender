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
        Animation(sf::Texture* texture, sf::Vector2f position, sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat);
        ~Animation();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target);
        void setAnimation(sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat);
        void setFrameSize(sf::Vector2i frameSize);
        void setRepeat(bool repeat);
        bool isFinished() const;
        void setDuration(sf::Time duration);
        void setNumFrames(std::size_t numFrames);
        sf::Sprite& getSprite();
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition() const;
        sf::IntRect getTextureRect();
        void move(float x, float y);

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