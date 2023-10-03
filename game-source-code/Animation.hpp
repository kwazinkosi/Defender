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
        Animation() = default; // Default constructor
        Animation(sf::Texture* texture,sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat);
        ~Animation();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target);
        void move(float x, float y);
        void setPosition(sf::Vector2f position);
        void setAnimation(sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat);
        void setFrameStart(sf::Vector2i frameStart){
            mFrameStart = frameStart;
        }
        void setFrameSize(sf::Vector2i frameSize);
        void setRepeat(bool repeat);
        bool isFinished() const;
        void setDuration(sf::Time duration);
        void setNumFrames(std::size_t numFrames);
        void setScale(float x, float y);
        sf::Sprite& getSprite();
        sf::Vector2f getPosition() const;
        sf::FloatRect getBounds() const;

    private:
        // Functions
        void setTextureRectToStart(sf::IntRect& textureRect);   // Set the texture rect to the start of the animation
        void updateFrameAndTextureRect(sf::IntRect& textureRect, const sf::Vector2i& textureBounds, const sf::Time& timePerFrame);
        void updateCurrentFrame();
        // Variables
        sf::Texture* texture;
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