#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Collidable.hpp"
#include <memory>
#include <vector>
#include "CommandQueue.hpp"
#include "Context.hpp"
#include "Utills.hpp"
#include "Entity.hpp"
#include "Projectile.hpp"
#include "Lander.hpp"
#include "PowerUp.hpp"
#include "Humanoid.hpp"



class Player: public Entity
{
    public:
        Player(Context &context, sf::Vector2f position);
        ~Player();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget &target);
        ENTITYTYPE getEntityType() const;
        void handleInput(CommandQueue& commands, sf::Event& event);
        void handleRealtimeInput(CommandQueue& commands);
        void onCollision();

        void shoot();
        void setPlayerState(PLAYERSTATE state);
        void setFuelBar();
        void setFuel(float fuel);
        void setLives(int lives);
        void addHumanoid(std::shared_ptr<Humanoid> humanoid);
        void removeHumanoid(std::shared_ptr<Humanoid> humanoid);
        int getHumanoidsCount() const;
        int getLives() const;
        void drawHUD(sf::RenderTarget &target);
        sf::Vector2f getPlayerPosition() const;
        // get bullets
        std::vector<std::unique_ptr<Projectile>>& getBullets();

    private:
        enum class Direction
        {
            IDLE = 0, UP, DOWN, LEFT, RIGHT,COUNT
        };
        void moveLeft(sf::Time deltaTime);
        void moveRight(sf::Time deltaTime);
        void moveUp(sf::Time deltaTime);
        void moveDown( sf::Time deltaTime);
        void shoot(sf::Time deltaTime);
        void screenWrap();
        void screenCollision();
        void initPlayer();
        void flipShip();
        void crashShip(sf::Time deltaTime);
        void updateInput(sf::Time deltaTime);
        void updateBullets(sf::Time deltaTime);
        void resqueHumanoid(sf::Time deltaTime);
        PLAYERSTATE mPlayerState;
        Context *mContext;
        CommandQueue *mCommandQueue;
        // vector of collidable objects
        std::vector<std::unique_ptr<Projectile>> mProjectiles; // This is the vector that will hold all the projectiles that the player shoots out.
        std::vector<std::shared_ptr<Humanoid>> mHumanoids; // This is the vector that will hold all the humanoids that the player rescues.
        Animation mAnimation[static_cast<int>(Direction::COUNT)]; // Array of spaceship animations
        // Variables for the player
        sf::Text mFuelBarText;
        sf::Vector2f mScale;
        sf::Clock mPlayerClock; 
        sf::Time mFuelTimer;
        sf::RectangleShape mFuelBar;
        sf::RectangleShape mFuelBarBackground;
        sf::Vector2f mPosition;
        Direction mCurrentAnimation;
        Direction mPreviousAnimation;
        float mLeftBound;
        float mRightBound;
        float mTopBound;
        float mBottomBound;
        int mLives;
        bool isLeft; // This is used to check if the player is moving left
        bool isSetDefault; // This is used to set the default animation for the player
        bool isSetAccelerate; // This is used to set the accelerate animation for the player
        float mCurrFuel;
        float mMaxFuel;
        float mFuelBurnRate;
        bool mIsShipFlipped;
};

#endif //PLAYER_H