#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <vector>
#include "Context.hpp"
#include "Utills.hpp"


class Player
{
    public:
        Player(Context &context); 
        ~Player();
        void update(sf::Time deltaTime);
        void drawPlayer(sf::RenderWindow &window);
        void setPlayerState(PLAYERSTATE state);

        sf::FloatRect getBoundingBox() const;
        sf::Vector2f getPosition() const;
        std::string getCollisionType() const;
        bool isStatic() const;
        void shoot();
        void move(sf::Vector2f movement);
        void ScreenCollision();
        void setPosition(float x, float y);

    private:
        PLAYERSTATE mPlayerState;
        sf::RectangleShape mPlayer;
        const float mPlayerSpeed = 100.0f;
        Context *mContext;
};

#endif //PLAYER_H