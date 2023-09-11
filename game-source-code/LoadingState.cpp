#include "LoadingState.hpp"

LoadingState::LoadingState(StateStack &stack, Context &context) : State(stack, context)
{


}

void LoadingState::centerOrigin(sf::Text &text)
{

}

void LoadingState::setCompletion(float percent)
{
}

void LoadingState::executeLoadingTask(sf::RenderWindow &window)
{
    mBackground.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    mBackground.setFillColor(sf::Color(50, 50, 50, 100));
    // Set the properties of the text
    
    mLoadingText.setFont(mLoadingFont);
    mLoadingString = "Loading";
    mLoadingText.setString(mLoadingString);
   // centerOrigin(mLoadingText);
    mLoadingText.setPosition(window.getSize().x / 2u, window.getSize().y / 2u + 50);

    mProgressBarBackground.setFillColor(sf::Color::White);
    mProgressBarBackground.setSize(sf::Vector2f(window.getSize().x - 20, 10));

    mProgressBarBackground.setPosition(10, mLoadingText.getPosition().y + 40);
    mProgressBar.setFillColor(sf::Color(100, 100, 100));

}

bool LoadingState::update(sf::Time dt)
{
}

bool LoadingState::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
}

std::string LoadingState::getStateID() const
{
    return "LoadingState";
}

void LoadingState::draw(sf::RenderWindow &window)
{
}

