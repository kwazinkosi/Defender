#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Collidable.hpp"
#include <memory>
#include <vector>
//#include "Animator.hpp"
#include "Context.hpp"
#include "Utills.hpp"


class Player: public Collidable
{
    public:
        Player(Context &context); 
        ~Player();
        void update(sf::Time deltaTime);
        void drawPlayer(sf::RenderWindow &window);
        void setPlayerState(PLAYERSTATE state);

        sf::FloatRect getBoundingBox() const;
        sf::FloatRect getCollisionBox() const;
        sf::Vector2f getPosition() const;
        std::string getCollisionType() const;
        void onCollision(Collidable* other);
        bool isStatic() const;
        std::string getCollisionResponse() const;
        void addCollidable(std::shared_ptr<Collidable> collidable);
        void shoot();
        void move(sf::Vector2f movement);
        void switchPlayerAnimation(PLAYERSTATE state);
        void ScreenCollision();
        void setPosition(float x, float y);

    private:
        std::vector<std::shared_ptr<Collidable>> collidables; // List of collidables that the player can collide with, shared_ptr because we want to share ownership of the collidable objects with other classes.
        PLAYERSTATE mPlayerState;
        //std::unique_ptr<Animator> mAnimator;
        //sf::Sprite mPlayer;
        sf::RectangleShape mPlayer;
        const float mPlayerSpeed = 100.0f;
        Context *mContext;
};

#endif //PLAYER_H