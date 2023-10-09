#include "Animation.hpp"

Animation::Animation(sf::Texture *texture, sf::Vector2i frameStart, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration, bool repeat)
{
    this->mSprite.setTexture(*texture);
    this->mFrameStart = frameStart;
    this->mFrameSize = frameSize;
    this->mNumFrames = numFrames;
    this->mCurrentFrame = 0;
    this->mDuration = duration;
    this->mElapsedTime = sf::Time::Zero;
    this->mRepeat = repeat;
    //std::cout << "Animation created --- to start at frame: " << mFrameStart.x << ", " << mFrameStart.y << " and end at frame: " << mNumFrames << " with duration: " << mDuration.asSeconds() << std::endl;
}

Animation::~Animation()
{
}

void Animation::setScale(float x, float y)
{
    this->mSprite.setScale(x, y);
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
    this->mFrameSize = frameSize;
}

void Animation::setNumFrames(std::size_t numFrames)
{
    this->mNumFrames = numFrames;
}

void Animation::setDuration(sf::Time duration)
{
    this->mDuration = duration;
}

void Animation::setRepeat(bool repeat)
{
    this->mRepeat = repeat;
}

void Animation::setPosition(sf::Vector2f position)
{
    this->mSprite.setPosition(position);
}

bool Animation::isFinished() const
{
    if(mCurrentFrame >= mNumFrames)
    {
        return true;
    }
    return false;
}

sf::Sprite& Animation::getSprite()
{
    return mSprite;
}

sf::FloatRect Animation::getBounds() const
{
    return mSprite.getGlobalBounds();
}

sf::Vector2f Animation::getPosition() const
{
    return this->mSprite.getPosition();
}

void Animation::draw(sf::RenderTarget &target)
{
    target.draw(this->mSprite);
}

void Animation::move(float x, float y)
{
    this->mSprite.setPosition(x, y);
}
void Animation::setSprite(sf::Sprite &sprite)
{
    sprite = this->mSprite; 
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

void Animation::update(sf::Time deltaTime)
{
   // Calculate the time per frame
    sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
    // Accumulate elapsed time
    mElapsedTime += deltaTime;
    // Get texture bounds and current texture rect
    sf::Vector2i textureBounds(mSprite.getTexture()->getSize());
    sf::IntRect textureRect(mSprite.getTextureRect());
    // Set the initial texture rect if the current frame is 0
    if (mCurrentFrame == 0)
    {
        setTextureRectToStart(textureRect); 
    }
    // Update animation frames
    while (mElapsedTime >= timePerFrame && (mCurrentFrame <= mNumFrames || mRepeat))
    {
        updateFrameAndTextureRect(textureRect, textureBounds, timePerFrame);
        updateCurrentFrame();
    }
    // Apply the updated texture rect to the sprite
    mSprite.setTextureRect(textureRect); 
}

void Animation::setTextureRectToStart(sf::IntRect& textureRect)
{
    textureRect = sf::IntRect(mFrameStart.x, mFrameStart.y, mFrameSize.x, mFrameSize.y);
}

void Animation::updateFrameAndTextureRect(sf::IntRect& textureRect, const sf::Vector2i& textureBounds, const sf::Time& timePerFrame)
{
    textureRect.left += textureRect.width;
    if (textureRect.left + textureRect.width > textureBounds.x)
    {
        textureRect.left = 0;
        textureRect.top += textureRect.height;
    }

    mElapsedTime -= timePerFrame;

    if (mRepeat)
    {
        mCurrentFrame = (mCurrentFrame + 1) % mNumFrames;
        if (mCurrentFrame == 0)
        {
            setTextureRectToStart(textureRect);
        }
    }
    else
    {
        mCurrentFrame++;
    }
}

void Animation::updateCurrentFrame()
{
    // Increment the current frame by 1
    if (!mRepeat && mCurrentFrame >= mNumFrames)
    {
        mCurrentFrame = mNumFrames - 1;
    }
}

