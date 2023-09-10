#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Game
{
    public:
        Game();
        ~Game();
        void runGame();

    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        const sf::Time mTimePerFrame = sf::seconds(1.f/60.f); // The time per frame, used to update the game state.
};

#endif // GAME_HPP

