#include "HelpState.hpp"

HelpState::HelpState(StateStack &stack, Context &context) : State(stack, context),
                                                              filePath_{"resources/files/help.txt"},
                                                              mContext(&context),
                                                              backgroundShape(),
                                                              helpText(),
                                                              mInstructionText(),
                                                              mTextFormater()
{
    std::cout << "HelpState::HelpState() -- Creating HelpState" << std::endl;
    font = context.mFonts->getResourceById(Fonts::SpaceObsessed);
    instructionFont = context.mFonts->getResourceById(Fonts::ArcadeN);

    onActivate();
    helpText.setFont(font);
    helpText.setString("Game Instructions");
    helpText.setFillColor(sf::Color::Yellow);
    helpText.setCharacterSize(30);
    mTextFormater.centerOrigin(helpText);
    helpText.setPosition(sf::Vector2f(0.21f * context.mWindow.getSize().x, 0.3f * context.mWindow.getSize().y));

    mInstructionText.setFont(font);
    mInstructionText.setString("[ Press Backspace to return to the main menu ]");
    mInstructionText.setCharacterSize(20);
    mTextFormater.centerOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * context.mWindow.getSize().x, 0.2f * context.mWindow.getSize().y);

    std::cout << "HighState::GameOverState() -- Done Creating HighState" << std::endl;
}

void HelpState::draw(sf::RenderWindow &window)
{
    window.setView(window.getDefaultView());
    window.draw(backgroundShape);
    window.draw(helpText);
    window.draw(mInstructionText);
    auto mInstructionText2 = mInstructionText;
    mInstructionText2.setString("[ Press Enter To Exit ]");
    mInstructionText2.setPosition(0.64f * mContext->mWindow.getSize().x, 0.1f * mContext->mWindow.getSize().y);
    window.draw(mInstructionText2);
    drawHelp(window);
}

bool HelpState::update(sf::Time dt)
{
    return false;
}


void HelpState::draw(sf::RenderWindow &window)
{
}

bool HelpState::update(sf::Time dt)
{
    return false;
}
