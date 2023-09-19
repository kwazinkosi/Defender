#include "PauseState.hpp"

PauseState::PauseState(StateStack &stack, Context &context) : State(stack, context)
{
    //ctor
}

void PauseState::draw(sf::RenderWindow &window)
{
     sf::Vector2u windowSize = window.getSize();

    // Draw the background first
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(20, 20, 20, 150));
    backgroundShape.setSize(sf::Vector2f(windowSize));

    // Set the paused text properties
    mPausedText = mTextFormater.formatText("Game Paused", sf::Vector2f(), sf::Color::White, sf::Text::Style::Regular, 30);
    mInstructionText = mTextFormater.formatText("Press Backspace to return to the game", sf::Vector2f(), sf::Color::White, sf::Text::Style::Regular, 20);
    mPausedText.setFont(mContext->mFonts->getResourceById(Fonts::SpaceObsessed));
    mInstructionText.setFont(mContext->mFonts->getResourceById(Fonts::SpaceObsessed));
    
    // Position the texts at the center of the window
    sf::Vector2f windowCenter = sf::Vector2f(windowSize) / 2.f;
    mPausedText.setOrigin(mPausedText.getLocalBounds().width / 2.f, mPausedText.getLocalBounds().height / 2.f);
    mInstructionText.setOrigin(mInstructionText.getLocalBounds().width / 2.f, mInstructionText.getLocalBounds().height / 2.f);
    mPausedText.setPosition(windowCenter.x, windowCenter.y - 50.f);
    mInstructionText.setPosition(windowCenter.x, windowCenter.y + 50.f);
    
    window.draw(backgroundShape);
    window.draw(mPausedText);
    window.draw(mInstructionText);

}
bool PauseState::update(sf::Time)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    // std::cout << "PauseState::handleEvent00" << std::endl;
    if (event.type == sf::Event::Closed)
    {
        requestStateClear(); // Clear the stack
        window.close();      // Close the window
    }

    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::BackSpace)
    {
        requestStackPop(); // Pop the pause state
    }

    return false; // Consume the event, don't pass it to lower states
}

void PauseState::handleRealtimeInput(sf::RenderWindow &window)
{
}

std::string PauseState::getStateID() const
{
    return "PauseState"; 
}