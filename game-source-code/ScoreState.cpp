#include "ScoreState.hpp"

ScoreState::ScoreState(StateStack &stack, Context &context) : State(stack, context),
                                                              filePath_{"resources/files/highscores.txt"},
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

bool ScoreState::handleEvent(const sf::Event &event, sf::RenderWindow &window)
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

void ScoreState::handleRealtimeInput(sf::RenderWindow &window)
{
}

void ScoreState::onActivate() // Called when the state is activated
{
    sf::Color backgroundColor(70, 30, 100, 100);
    backgroundShape.setFillColor(backgroundColor);
    backgroundShape.setSize(sf::Vector2f(mContext->mWindow.getSize()));
}

void ScoreState::drawScore(sf::RenderWindow &window)
{
    std::string line;
    file.open(filePath_, std::ios::in);
    float ySpacing = 0.35f;

    static float increment = 0.0f;
    int rank = 1;
    while (std::getline(file, line))
    {

        std::cout << line << std::endl;
        sf::Text text;
        text.setFont(font);
        text.setFillColor(sf::Color::Yellow);
        text.setString(std::to_string(rank) + ".    " + line);
        text.setCharacterSize(20);
        text.setPosition(sf::Vector2f(0.5f * mContext->mWindow.getSize().x - text.getGlobalBounds().width / 2.0f,
                                      ySpacing * mContext->mWindow.getSize().y + increment));
        window.draw(text);
        rank++;
        increment += 25.f;
    }
    increment = 0.0f;
    file.close();
}

std::string ScoreState::getStateID() const
{
    return "ScoreState";
}
