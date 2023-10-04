#include "Game.hpp"

#include <vector>

#include <time.h>

int main()
{

    
   srand(time(NULL)); // seed the random number generator
    try
    {
        Game game;
        game.runGame();
    }
    catch (std::exception &e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;

    }

    return 0;
}