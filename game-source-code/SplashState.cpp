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
    mBackgroundSprite.setTexture(mContext->mBackgrounds->getResourceById(Backgrounds::SplashScreen));
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
/**
 * @brief Updates the splash screen.
 * 
 * @param dt The time elapsed since the last update.
 * @return true 
 */
bool SplashState::update(sf::Time dt) 
{
    mElapsedTime += dt;
    if (mElapsedTime >= sf::seconds(0.7f))
    {  
        //std::cout << "Updating the SplashState::update() function" << dt.asSeconds() << std::endl;
        mShowText = !mShowText;
        mElapsedTime = sf::Time::Zero;
    }
    return true;
}

/**
 * @brief Handles the splash screen events.
 * 
 * If the user presses any key, the splash screen is popped from the stack and the menu screen is pushed onto the stack.
 * 
 * @param event The event to be handled.
 * @return true 
 * @return false 
 */
bool SplashState::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::Closed)
    {
        std::cout << "Closing the window, in SplashState.cpp| handleEvent() function" << std::endl;
        requestStateClear(); // Clear the stack
        window.close();
    }
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::MainMenuState);
    }
    return true;
}

void SplashState::handleRealtimeInput(sf::RenderWindow &window)
{
}

std::string SplashState::getStateID() const
{
    return "SplashState";
}