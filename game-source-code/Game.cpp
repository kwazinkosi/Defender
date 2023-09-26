#include "Game.hpp"

Game::Game()
{
    registerStates();
}

Game::~Game()
{
}

/**
 * @brief Registers all the game states.
 *
 * This function registers all the game states by calling the registerState() function for each state.
 * The registerState() function is a template function that takes a state ID and a state object as arguments.
 * The state ID is used to identify the state, and the state object is used to create the state.
 * 
 * This function should be called once in the constructor of Game.
 */
void Game::registerStates()
{
    
    mStateStack.registerState<LoadingState>(States::LoadingState, mContext);
    mStateStack.registerState<SplashState>(States::SplashState, mContext);
    mStateStack.registerState<MainMenuState>(States::MainMenuState, mContext);
    //mStateStack.registerState<HelpState>(States::HelpState, mContext);
    mStateStack.registerState<GameState>(States::GameState, mContext);
    mStateStack.registerState<GameOverState>(States::GameOverState, mContext);
    mStateStack.registerState<PauseState>(States::PauseState, mContext);

    //std::cout<<"Done registering"<<std::endl;
    //mStateStack.registerState<OptionsState>(States::OptionsState, mContext);
    mStateStack.pushState(States::LoadingState);
}
/**
 * @brief The main game loop responsible for running the game.
 *
 *This function contains the main game loop, which continuously updates the game state and renders the game until the window is closed.
 * A fixed time step is used to update the game state. This means that the game state is updated at a fixed rate regardless of the frame rate.
 * 
 * The loop iterates until the game window is open. In each iteration, it performs the following steps:
 * - Measures the time elapsed since the last update (timeSinceLastUpdate) using a clock.
 * - Processes all the events in the event queue (e.g., keyboard input, window close).
 * - Updates the game state based on the elapsed time (deltaTime).
 * - Renders the updated game state to the window for display.
 * 
 */
void Game::runGame()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mContext.mWindow.isOpen())
    {
        //At this point, a new frame has started, so we need to measure the time elapsed since the last frame. 
        timeSinceLastUpdate += clock.restart();  // restart() returns the time elapsed since the last restart() call
       
        while (timeSinceLastUpdate > mTimePerFrame)
        {
            //At this point, we have accumulated enough time to update the game state.
            timeSinceLastUpdate -= mTimePerFrame;
            processEvents();
            update(mTimePerFrame);  // update() is a private member function of Game that updates the game state
        }
        render(); // render() renders the game state to the window for display

    }
}

/**
 * @brief Processes all the events in the event queue.
 *
 * This function processes all the events in the event queue by iterating through each event
 * and handling the event accordingly.
 * The event queue contains all the events that have occurred since the last iteration of the game loop.
 * 
 * The event loop iterates until the event queue is empty. In each iteration, it performs the following steps:
 * - Gets the next event in the queue.
 * - Handles the event accordingly.
 * - Removes the event from the queue.
 * 
 */
void Game::processEvents()
{
    sf::Event event;
    while (mContext.mWindow.pollEvent(event))
    {
       mStateStack.handleEvent(event, mContext.mWindow);
    }
    mStateStack.handleRealtimeInput(mContext.mWindow);
}

/**
 * @brief Updates the game based on the elapsed time.
 *
 * This function updates the game state based on the elapsed time (deltaTime).
 *
 * @param deltaTime The time elapsed since the last iteration of the game loop.
 */
void Game::update(sf::Time deltaTime)
{
    mStateStack.update(deltaTime);
}

/**
 * @brief Renders the game state to the window for display.
 *
 * This function renders the game to the window for display.
 */
void Game::render()
{
    mContext.mWindow.clear();
    mStateStack.draw(mContext.mWindow);
    mContext.mWindow.display();
}
