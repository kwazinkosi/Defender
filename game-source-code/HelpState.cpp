#include "HelpState.hpp"

HelpState::HelpState(StateStack &stack, Context &context) 
: State(stack, context),
mContext(&context),
filePath_{"resources/files/help.txt"}
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

bool HelpState::handleEvent(const sf::Event &event, sf::RenderWindow &window)
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

void HelpState::handleRealtimeInput(sf::RenderWindow &window)
{
}

void HelpState::onActivate() // Called when the state is activated
{
    sf::Color backgroundColor(70, 30, 100, 100);
    backgroundShape.setFillColor(backgroundColor);
    backgroundShape.setSize(sf::Vector2f(mContext->mWindow.getSize()));
}
void HelpState::drawHelp(sf::RenderWindow &window)
{
    std::string line;
    file.open(filePath_, std::ios::in);
    float ySpacing = 0.35f;

    static float increment = 0.0f;
    
    while (std::getline(file, line))
    {

        // std::cout << line << std::endl;
        sf::Text text;
        text.setFont(instructionFont);
        text.setFillColor(sf::Color::White);
        text.setString(line);
        text.setCharacterSize(12);
        text.setPosition(sf::Vector2f(0.05f * mContext->mWindow.getSize().x ,
                                      ySpacing * mContext->mWindow.getSize().y + increment));
        window.draw(text);
        increment += 25.f;
    }
    increment = 0.0f;
    file.close();
}
std::string HelpState::getStateID() const
{
    return "HelpState";
}