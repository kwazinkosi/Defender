#include "GameOverState.hpp"

GameOverState::GameOverState(StateStack& stack, Context &context):
    State(stack, context),
    mContext(&context),
    backgroundShape(),
    mGameOverText(),
    mInstructionText(),
    mTextFormater()
{
    std::cout <<"GameOverState::GameOverState() -- Creating GameOverState"<< std::endl;
    sf::Font &font = context.mFonts->getResourceById(Fonts::SpaceObsessed);
    
    onActivate();
    mGameOverText.setFont(font);
    mGameOverText.setString("Game Over");
    mGameOverText.setCharacterSize(50);
    mTextFormater.centerOrigin(mGameOverText);
    mGameOverText.setPosition(sf::Vector2f(0.5f * context.mWindow.getSize().x, 0.4f * context.mWindow.getSize().y));

    mInstructionText.setFont(font);
    mInstructionText.setString("[ Press Backspace to return to the main menu ]");
    mInstructionText.setCharacterSize(20);
    mTextFormater.centerOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * context.mWindow.getSize().x, 0.6f * context.mWindow.getSize().y);
    
}

GameOverState::~GameOverState()
{
}

void GameOverState::draw(sf::RenderWindow &window)
{
     window.setView(window.getDefaultView());
    window.draw(backgroundShape);
    window.draw(mGameOverText);
    window.draw(mInstructionText);
    auto mInstructionText2 = mInstructionText;
    mInstructionText2.setString("[ Press Enter To Exit ]");
    mInstructionText2.setPosition(0.64f * mContext->mWindow.getSize().x, 0.7f * mContext->mWindow.getSize().y);
    window.draw(mInstructionText2);
}

bool GameOverState::update(sf::Time dt)
{
    return false;
}

bool GameOverState::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
    {
        requestStackPop();
        requestStackPush(States::MainMenuState);
    }
     if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))
    {
        requestStateClear(); // Clear the stack
        window.close();      // Close the window
    }


    return false;
}

void GameOverState::handleRealtimeInput(sf::RenderWindow &window)
{
}

std::string GameOverState::getStateID() const
{
    return "GameOverState";
}

void GameOverState::onActivate() // Called when the state is activated
{
    sf::Color backgroundColor(70, 30, 100, 100);
    backgroundShape.setFillColor(backgroundColor);
    backgroundShape.setSize(sf::Vector2f(mContext->mWindow.getSize()));
}
