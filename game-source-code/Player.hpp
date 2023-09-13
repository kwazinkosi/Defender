#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Context.hpp"
#include "Utills.hpp"


class Player
{
    public:
        Player(Context &context); 
        ~Player();
};

#endif //PLAYER_H