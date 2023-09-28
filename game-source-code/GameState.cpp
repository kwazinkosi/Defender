#include "GameState.hpp"

GameState::GameState(StateStack &stack, Context &context) : State(stack, context), mIsPaused(false)
{    
    std::cout << "1. GameState::GameState()\n";
     try {
        mWorld =std::make_unique<World>(context);
        mBackgroundSprite.setTexture(mContext->mBackgrounds->getResourceById(Backgrounds::MainMenuScreen));
        std::cout << "3. GameState::GameState() - Background set\n";
        
        // Set the text
        mText.setFont(mContext->mFonts->getResourceById(Fonts::SpaceObsessed));
        std::cout << "4. GameState::GameState() - Text font set\n";
    } catch (const std::exception& e) {
        std::cerr << "Error in GameState constructor: " << e.what() << std::endl;
    }
    std::cout <<"GameState::GameState() -- Done constructing gamestate" <<std::endl;
}

void GameState::pauseGame()
{ 
    requestStackPush(States::PauseState);
    std::cout << "GameState::pauseGame()\n";
}

void GameState::gameOver()
{
    requestStackPop(); // Pop the game state
    std::cout << "GameState::gameOver()"<<std::endl;
    requestStackPush(States::GameOverState); // Push the game over state
}

void GameState::draw(sf::RenderWindow &window)
{
   mWorld->render();
}

bool GameState::update(sf::Time dt)
{
    //std::cout << "GameState::update() -- Updating game state" << std::endl;
   // Update the player
    auto gameResult = mWorld->update(dt);
    //std::cout << "GameState::update() -- Game result: " << gameResult.first << std::endl;
    if (gameResult.first == true)
    {
        gameOver();

    }
    
    return true;
}

bool GameState::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    auto ev = event;
    auto commands = mWorld->getCommandQueue(); // get command queue from world
    
    if (event.type == sf::Event::Closed )
    {
        requestStateClear(); // Clear the stack
        window.close();      // Close the window
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P )
    {
        pauseGame();
        std::cout << "GameState::handleEvent() -- Paused game" << std::endl;
    }
    

    mWorld->handleInput(*commands, ev);
    return true; // Consume the event, don't pass it to lower states
}

void GameState::handleRealtimeInput(sf::RenderWindow &window)
{
    auto commands = mWorld->getCommandQueue(); // get command queue from world
    mWorld->handleRealtimeInput(*commands);
}

std::string GameState::getStateID() const
{
    return "GameState";
}

