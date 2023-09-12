#include "GameState.hpp"

GameState::GameState(StateStack &stack, Context &context) : State(stack, context){std::cout << "1. GameState::GameState()\n";
     try {
        std::cout << "2. GameState::GameState() - Player created\n";
        
        mBackgroundSprite.setTexture(mContext->mBackgrounds->getResourceById(Backgrounds::MainMenuScreen));
        std::cout << "3. GameState::GameState() - Background set\n";
        
        // Set the text
        mText.setFont(mContext->mFonts->getResourceById(Fonts::SpaceObsessed));
        std::cout << "4. GameState::GameState() - Text font set\n";
    } catch (const std::exception& e) {
        std::cerr << "Error in GameState constructor: " << e.what() << std::endl;
    }
}

// This function handles the player input, it is called from the handleEvent() function in the GameState class.
void GameState::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    
}

void GameState::pauseGame()
{
}

void GameState::gameOver()
{
}

void GameState::draw(sf::RenderWindow &window)
{
}

bool GameState::update(sf::Time dt)
{
}

bool GameState::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::Closed)
    {
        requestStateClear(); // Clear the stack
        window.close();      // Close the window
    }
}

std::string GameState::getStateID() const
{
    return "GameState";
}

