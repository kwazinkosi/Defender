#include "Context.hpp"

Context::Context(): 
mWindow(sf::VideoMode(800, 600), "Defender Shooter", sf::Style::Close)
, mWorldView(sf::FloatRect(0.f, 125.f, 800.f, 475.f)) // Starts below the HUD and Minimap
, mMiniMapView(sf::FloatRect(205.f, 0.f, 400.f, 120.f)) // Side by side with HUD, same height
, mHudView(sf::FloatRect(0.f, 0.f, 200.f, 120.f)) // Side by side with Minimap, same height
, mMapRect(sf::Vector2f(mMiniMapView.getSize().x, mMiniMapView.getSize().y))
, mHudRect(sf::Vector2f(mHudView.getSize().x, mHudView.getSize().y))
, mWorldRect(sf::Vector2f(mWorldView.getSize().x, mWorldView.getSize().y))
{
    // Define the viewport for each view
    mWorldView.setViewport(sf::FloatRect(0.f, 0.208f, 1.f, 0.791f)); // Bottom 73.3% of the window
    mMiniMapView.setViewport(sf::FloatRect(0.2563f, 0.f, 0.5f, 0.2f)); // Side by side with HUD, 20% height
    mHudView.setViewport(sf::FloatRect(0.0f, 0.f, 0.25f, 0.2f)); // Side by side with Minimap, 20% height

    mBackgrounds = std::make_unique<BackgroundsHolder>();
    mFonts = std::make_unique<FontsHolder>();
    mTextures = std::make_unique<TexturesHolder>();

    if (!mBackgrounds || !mFonts || !mTextures)
    {
        throw ContextInitializationException{};
    }
    // Initialize the map rectangle
    mMapRect.setSize(sf::Vector2f(mMiniMapView.getSize().x, mMiniMapView.getSize().y));
    mMapRect.setFillColor(sf::Color(50, 50, 120, 255));
    mMapRect.setPosition(mMiniMapView.getCenter().x - mMapRect.getSize().x / 2.f, mMiniMapView.getCenter().y - mMapRect.getSize().y / 2.f);

    // Initialize the HUD rectangle
    mHudRect.setSize(sf::Vector2f(mHudView.getSize().x, mHudView.getSize().y));
    mHudRect.setFillColor(sf::Color(50, 80, 100, 50));
    mHudRect.setPosition(mHudView.getCenter().x - mHudRect.getSize().x / 2.f, mHudView.getCenter().y - mHudRect.getSize().y / 2.f);

    // Initialize the world rectangle

    mWorldRect.setSize(sf::Vector2f(mWorldView.getSize().x, mWorldView.getSize().y));
    mWorldRect.setFillColor(sf::Color(50, 50, 100, 10));
    mWorldRect.setPosition(mWorldView.getCenter().x - mWorldRect.getSize().x / 2.f, mWorldView.getCenter().y - mWorldRect.getSize().y / 2.f);

    // Initialize the bounds
    mLeftBound =mWorldView.getCenter().x - mWorldView.getSize().x / 2.f;
    mRightBound =mWorldView.getCenter().x + mWorldView.getSize().x / 2.f;
    mTopBound =mWorldView.getCenter().y - mWorldView.getSize().y / 2.f;
    mBottomBound =mWorldView.getCenter().y + mWorldView.getSize().y / 2.f;
    std::cout<<"Left: "<<mLeftBound<<" Right: "<<mRightBound<<" Top: "<<mTopBound<<" Bottom: "<<mBottomBound<<std::endl;
}
Context::~Context()
{
    //dtor
} 
