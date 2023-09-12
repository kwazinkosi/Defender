#include "MainMenuState.hpp"

MainMenuState::MainMenuState(StateStack &stack, Context &context) : State(stack, context)
{
    //loading of resources is done in the constructor of the State class 
    mText.setFont(mContext->mFonts->getResourceById(Fonts::SpaceObsessed));
    mBackgroundSprite.setTexture(mContext->mBackgrounds->getResourceById(Backgrounds::MainMenuScreen));

    // Set the text
    setupMenuOptions();
    mMenuOptionsIterator = mMenuOptions.begin();
}
//function is called from the StateStack class
void MainMenuState::draw(sf::RenderWindow &window)
{
    //window.clear();
    window.draw(mBackgroundSprite);
    drawMenuOptions(window);
    //window.display();
}

//function is called from the StateStack class in the update() function of the StateStack class.
bool MainMenuState::update(sf::Time dt)
{
    return true; // TO DO: Change this to false if you want to stop the game from running
}