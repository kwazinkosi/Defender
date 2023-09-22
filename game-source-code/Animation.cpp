#include "Animation.hpp"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::update(sf::Time deltaTime)
{
}

void Animation::draw(sf::RenderTarget &target)
{
}

void Animation::setAnimation(sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat)
{
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
}

void Animation::setRepeat(bool repeat)
{
}

bool Animation::isFinished() const
{
    return false;
}

void Animation::setDuration(sf::Time duration)
{
}

void Animation::setNumFrames(std::size_t numFrames)
{
}

sf::Sprite &Animation::getSprite()
{
    // TODO: insert return statement here
}

void Animation::setPosition(sf::Vector2f position)
{
}

sf::Vector2f Animation::getPosition() const
{
    return sf::Vector2f();
}

sf::IntRect Animation::getTextureRect()
{
    return sf::IntRect();
}

void Animation::move(float x, float y)
{
}
