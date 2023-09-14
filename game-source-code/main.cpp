#include "Game.hpp"
#include <time.h>

int main()
{
    srand(time(NULL)); // seed the random number generator

    try
    {
        Game game;
        game.run();
    }
    catch (std::exception &e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}