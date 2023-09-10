#include "Context.hpp"

Context::Context() : mWindow(sf::VideoMode(800, 600), "Defender Shooter", sf::Style::Close)
{
    mBackgrounds = std::make_unique<BackgroundsHolder>();
    mFonts = std::make_unique<FontsHolder>();
    mTextures = std::make_unique<TexturesHolder>();

    if (!mBackgrounds || !mFonts || !mTextures)
    {
        throw ContextInitializationException{};
    }
}

Context::~Context()
{
    // dtor
}