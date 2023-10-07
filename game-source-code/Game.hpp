#ifndef GAME_HPP
#define GAME_HPP

#include "Context.hpp"
#include "StateStack.hpp"
#include "Player.hpp"
#include "LoadingState.hpp"
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "ScoreState.hpp"
#include "HelpState.hpp"
#include "GameOverState.hpp"

class Game
{
    public:
        Game();
        ~Game();
        void run();

    private:
        void registerStates();
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        const sf::Time mTimePerFrame = sf::seconds(1.f/60.f); // The time per frame, used to update the game state.
        StateStack mStateStack;
        Context mContext; // The context of the game (e.g., window, resource managers).
};

#endif // GAME_HPP

