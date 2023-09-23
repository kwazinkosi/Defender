#include "Mountains.hpp"

Mountains::Mountains(Context &context, bool isLeft, float scrollSpeed, float posY)
    : mWorldView(&context.mWorldView), mScrollSpeed(scrollSpeed), mIsLeftScrolling(isLeft), mPosY(posY)
{
    // Load texture
    mMountainTexture = context.mBackgrounds->getResourceById(Backgrounds::Mountains);
    // Set texture to repeat
    mMountainTexture.setRepeated(true);
    // Initialize mountains
    initMountains();
    viewLeft = mWorldView->getCenter().x - mWorldView->getSize().x / 2.f;
    viewRight = mWorldView->getCenter().x + mWorldView->getSize().x / 2.f;
    std::cout << "View position: " << mWorldView->getCenter().x << " | View left: " << mWorldView->getCenter().x - mWorldView->getSize().x / 2.f << " | View right: " << mWorldView->getCenter().x + mWorldView->getSize().x / 2.f << std::endl;
}

Mountains::~Mountains()
{
    //dtor
}

void Mountains::initMountains()
{
    // set texture to repeat
    auto mountainSprite1 = sf::Sprite(mMountainTexture);
    auto mountainSprite2 = sf::Sprite(mMountainTexture);
    mountainSprite1.setScale(1.f, 1.33f);
    mountainSprite2.setScale(1.f, 1.33f);
    mMountainBounds = mountainSprite1.getGlobalBounds();
    auto posY = mWorldView->getSize().y -2.f; //- mMountainBounds.height - 30.f;
    // set position at bottom of screen
    mountainSprite1.setPosition(0.f, posY);                   // x = 0, y = 452,
    mountainSprite2.setPosition(mMountainBounds.width, posY); // Chain the sprites together
    // insert mountain sprites into vector
    mMountains.push_back(mountainSprite1);
    mMountains.push_back(mountainSprite2);
    std::cout << "Mountain bounds: " << mMountainBounds.left << " | " << mMountainBounds.top << " | " << mMountainBounds.width << " | " << mMountainBounds.height << std::endl;
}

void Mountains::update(sf::Time deltaTime)
{
    if (mMountains.empty())
        throw std::runtime_error("Mountains vector is empty!");
    // Check if view is set
    if (mWorldView == nullptr)
        throw std::runtime_error("View is not set!");

    viewLeft = mWorldView->getCenter().x - mWorldView->getSize().x / 2.f;  // get left side of view == 0.f
    viewRight = mWorldView->getCenter().x + mWorldView->getSize().x / 2.f; // get right side of view == 800.f
    std::cout << "Mountains::update() -- View position: " << mWorldView->getCenter().x << " | View left: " << viewLeft << " | View right: " << viewRight << std::endl;
    if (viewLeft < mMountainBounds.left)
    {
        // Wrap view around to the right of the mountain
        mWorldView->setCenter(mMountainBounds.left + mWorldView->getSize().x / 2.f, mWorldView->getCenter().y);
    }
    else if (viewRight > mMountainBounds.left + mMountainBounds.width)
    {
        // Wrap view around to the left of the mountain
        mWorldView->setCenter(mMountainBounds.left + mMountainBounds.width - mWorldView->getSize().x / 2.f, mWorldView->getCenter().y);
    }
}

