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
/**
 * @brief This function handles the events.
 * 
 * The function handles the events and returns true if the event is handled and false if it is not handled.
 * - If the Up key is pressed, the iterator is decremented.
 * - If the Down key is pressed, the iterator is incremented.
 * - If the Return key is pressed, the state is popped from the stack and the game state is pushed onto the stack.
 * 
 * The function also calls the updateOptionText() function to update the text of the menu options 
 * 
 * @param event  The event to be handled.
 * @return true 
 * @return false 
 */
bool MainMenuState::handleEvent(const sf::Event &event, sf::RenderWindow &window) 
{
    //std::cout<<"Inside Menu handleEvent\n";
    if (event.type == sf::Event::Closed)
    {
        requestStateClear(); // Clear the stack
        window.close(); // Close the window 
    }
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            // If the iterator is at the beginning, set it to the end - 1
            if (mMenuOptionsIterator == mMenuOptions.begin())
            {
                mMenuOptionsIterator = mMenuOptions.end() - 1;
            }
            else
            {
                --mMenuOptionsIterator; // Otherwise, decrement it
            }
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
           // If the iterator is at the end - 1, set it to the beginning 
            if (mMenuOptionsIterator == mMenuOptions.end() - 1)
            {
                mMenuOptionsIterator = mMenuOptions.begin();
            }
            else{
                ++mMenuOptionsIterator; // Otherwise, increment it
            }
        }
        else if (event.key.code == sf::Keyboard::Return)
        {
            if (mMenuOptionsIterator == mMenuOptions.begin())
            {
                requestStackPop();
                requestStackPush(States::GameState);
            }
            else if (mMenuOptionsIterator == mMenuOptions.begin() + 1)
            {
                // requestStackPop();
                // requestStackPush(States::HelpState);
            }
             else if (mMenuOptionsIterator == mMenuOptions.begin() + 2)
            {
                // requestStackPop();
                // requestStackPush(States::ExitState);
            }
            else if (mMenuOptionsIterator == mMenuOptions.begin() + 3)
            {
                // requestStackPop();
                // requestStackPush(States::ExitState);
            }
        }
    }
    updateOptionText();
    return true;
}