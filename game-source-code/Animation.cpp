#include "Animation.hpp"

Animation::Animation(sf::Texture *texture, sf::Vector2f position, sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat)
    : mSprite(*texture), mFrameStart(frameStart), mFrameSize(frameSize), mNumFrames(numFrames), mCurrentFrame(0), mDuration(duration), mElapsedTime(sf::Time::Zero), mPosition(position), mRepeat(repeat)
{
     //std::cout << "Animation::Animation() --- to start at frame: " << mFrameStart.x << ", " << mFrameStart.y << " and end at frame: " << mNumFrames << " with duration: " << mDuration.asSeconds() <<" starting at position: " << mPosition.x << ", " << mPosition.y << std::endl;
    this->mSprite.setTexture(*texture);
    this->mSprite.setTextureRect(sf::IntRect(mFrameStart.x, mFrameStart.y, mFrameSize.x, mFrameSize.y));
    this->mSprite.setScale(4.f, 4.f);
    this->mSprite.setPosition(position);
}

Animation::~Animation()
{
}

void Animation::update(sf::Time deltaTime)
{
    sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames); // How long each frame lasts
    mElapsedTime += deltaTime;

    sf::Vector2i textureBounds(mSprite.getTexture()->getSize()); // Get the size of the texture
    sf::IntRect textureRect(mSprite.getTextureRect()); // Get the current texture rect, which is the current frame
    
    // If the current frame is 0, then set the texture rect to the first frame
    if (mCurrentFrame == 0)
    {
        textureRect = sf::IntRect(mFrameStart.x, mFrameStart.y, mFrameSize.x, mFrameSize.y);
    }
    
    // If the elapsed time is greater than the time per frame, then we need to move to the next frame in the animation.
    while (mElapsedTime >= timePerFrame && (mCurrentFrame <= mNumFrames || mRepeat))
    {
        // Move the texture rect to left by the width of the frame
        textureRect.left += textureRect.width;
        // If we reach the end of the texture, then move the texture rect down by the height of the frame and reset the left to 0
        if (textureRect.left + textureRect.width > textureBounds.x)
        {
            //std::cout << "Reached the end of the texture." << std::endl;
            textureRect.left = 0; // Reset the left
            textureRect.top += textureRect.height; // Move the top down by the height of the frame
        }
        
        mElapsedTime -= timePerFrame; // Subtract the time per frame from the elapsed time because we are moving to the next frame
        if (mRepeat)
        {
            // Increment the current frame by 1 and then mod it by the number of frames to get the remainder, which will be the current frame
            mCurrentFrame = (mCurrentFrame + 1) % mNumFrames; 
            if (mCurrentFrame == 0)
            {
                textureRect = sf::IntRect(mFrameStart.x, mFrameStart.y, mFrameSize.x, mFrameSize.y);
            }
        }
        else
        {
            mCurrentFrame++; // Increment the current frame by 1
        }
    }
    mSprite.setTextureRect(textureRect); // Set the texture rect to the new frame
    mSprite.setScale(4.f, 4.f);
 
}

void Animation::draw(sf::RenderTarget &target)
{
    target.draw(this->mSprite);
}

void Animation::setAnimation(sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat)
{
    this->mFrameStart = frameStart;
    this->mFrameSize = frameSize;
    this->mNumFrames = numFrames;
    this->mCurrentFrame = 0;
    this->mDuration = duration;
    this->mElapsedTime = sf::Time::Zero;
    this->mRepeat = repeat;
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
    this->mFrameSize = frameSize;
}

void Animation::setRepeat(bool repeat)
{
    this->mRepeat = repeat;
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
