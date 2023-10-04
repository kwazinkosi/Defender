#include "ScoreState.hpp"

ScoreState::ScoreState(StateStack &stack, Context &context) : State(stack, context),
                                                              filePath_{"resources/files/highscore.txt"},
                                                              mContext(&context),
                                                              backgroundShape(),
                                                              HighScoreText(),
                                                              mInstructionText(),
                                                              mTextFormater()
{
    std::cout << "ScoreState::ScoreState() -- Creating ScoreState" << std::endl;
    font = context.mFonts->getResourceById(Fonts::SpaceObsessed);

    onActivate();
    HighScoreText.setFont(font);
    HighScoreText.setString("High Score");
    HighScoreText.setFillColor(sf::Color::Yellow);
    HighScoreText.setCharacterSize(30);
    mTextFormater.centerOrigin(HighScoreText);
    HighScoreText.setPosition(sf::Vector2f(0.5f * context.mWindow.getSize().x, 0.3f * context.mWindow.getSize().y));

    mInstructionText.setFont(font);
    mInstructionText.setString("[ Press Backspace to return to the main menu ]");
    mInstructionText.setCharacterSize(20);
    mTextFormater.centerOrigin(mInstructionText);
    mInstructionText.setPosition(0.5f * context.mWindow.getSize().x, 0.2f * context.mWindow.getSize().y);

    std::cout << "HighState::GameOverState() -- Done Creating HighState" << std::endl;
}

void ScoreState::draw(sf::RenderWindow &window)
{
    window.setView(window.getDefaultView());
    window.draw(backgroundShape);
    window.draw(HighScoreText);
    window.draw(mInstructionText);
    auto mInstructionText2 = mInstructionText;
    mInstructionText2.setString("[ Press Enter To Exit ]");
    mInstructionText2.setPosition(0.64f * mContext->mWindow.getSize().x, 0.1f * mContext->mWindow.getSize().y);
    window.draw(mInstructionText2);
    drawScore(window);
}

bool ScoreState::update(sf::Time dt)
{
    return false;
}
