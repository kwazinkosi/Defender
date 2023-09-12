#include "SplashState.hpp"

/**
 * @brief Construct a new Splash Screen:: Splash Screen object.
 * 
 * @param stack The state stack object.
 */
SplashState::SplashState(StateStack &stack, Context &context) :State(stack, context)
                                                , mBackgroundSprite()
                                                , mText()
                                                , mElapsedTime(sf::Time::Zero)
                                                , mShowText(false)
{
    std::cout<<"Creating Splash State" << std::endl;
    //mKeypadSprite.setTexture(mContext->mTextures->getResourceById(Textures::Keypad));
    mBackgroundSprite.setTexture(mContext->mBackgrounds->getResourceById(Backgrounds::MainMenuScreen));
    mBackgroundSprite.setScale(0.5f, 0.5f);
   // mKeypadSprite.setScale(0.1f, 0.1f);
    mText =mTextFormater.formatText("Press any key to continue", sf::Vector2f(200.0f, 250.0f), sf::Color::White, sf::Text::Style::Bold, 30);
    mText.setFont(mContext->mFonts->getResourceById(Fonts::SpaceObsessed));
    //mKeypadSprite.setPosition(300.f, 300.f);
    std::cout<<"Done Creating Splash State" << std::endl;
}

/**
 * @brief Draws the splash screen.
 * 
 */
void SplashState::draw(sf::RenderWindow &window)
{
    window.draw(mBackgroundSprite);
    if (mShowText){
        window.draw(mText);
    }

     //window.draw(mKeypadSprite);


}