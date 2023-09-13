#include "GameState.hpp"

GameState::GameState(StateStack &stack, Context &context) : State(stack, context), mPlayer(nullptr), mIsPaused(false)
{std::cout << "1. GameState::GameState()\n";
     try {
        mPlayer = std::make_unique<Player>(context);
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
    if (key == sf::Keyboard::Escape && !isPressed)
    {
        gameOver();
    }
    else if (key == sf::Keyboard::BackSpace && !isPressed)
    {
        pauseGame();
    }
    else
    {
        // Handle movement keys (Up, Down, Left, Right)
        if (key == sf::Keyboard::Left)
        {
            mPlayer->setPlayerState(PLAYERSTATE::MOVINGLEFT);
            mPlayer->switchPlayerAnimation(PLAYERSTATE::MOVINGLEFT);
            
        }
        else if (key == sf::Keyboard::Right)
        {
            mPlayer->setPlayerState(PLAYERSTATE::MOVINGRIGHT);
            mPlayer->switchPlayerAnimation(PLAYERSTATE::MOVINGRIGHT);
        }
        else if (key == sf::Keyboard::Up)
        {
            mPlayer->setPlayerState(PLAYERSTATE::MOVINGUP);
        }
        else if (key == sf::Keyboard::Down)
        {
            mPlayer->setPlayerState(PLAYERSTATE::MOVINGDOWN);
        }
        else if (key == sf::Keyboard::Space)
        {
            mPlayer->setPlayerState(PLAYERSTATE::SHOOTING);
        }
        else
        {
            mPlayer->setPlayerState(PLAYERSTATE::IDLE);
        }
    }
}

void GameState::pauseGame()
{ 
    requestStackPush(States::PauseState);
    std::cout << "GameState::pauseGame()\n";
}

void GameState::gameOver()
{
    requestStackPush(States::GameOverState);
}

void GameState::draw(sf::RenderWindow &window)
{
    window.draw(mBackgroundSprite);
    
    window.draw(mText);
    mPlayer->drawPlayer(window);
}

bool GameState::update(sf::Time dt)
{
    // Update the player
    mPlayer->update(dt);
    return true;
}

bool GameState::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::Closed)
    {
        requestStateClear(); // Clear the stack
        window.close();      // Close the window
    }
    if (event.type == sf::Event::KeyPressed)
    {
        handlePlayerInput(event.key.code, true);
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        //handlePlayerInput(event.key.code, false);
        //mPlayer->move(sf::Vector2f(0.f, 0.f)); // Stop the player from moving
         mPlayer->setPlayerState(PLAYERSTATE::IDLE);
    }

    return true; // Consume the event, don't pass it to lower states
}

std::string GameState::getStateID() const
{
    return "GameState";
}

