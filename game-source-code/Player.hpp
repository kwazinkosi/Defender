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
    /**
     * @brief Construct a new Player object
     * 
     * @param context 
     * @param position 
     */
        Player(Context &context, sf::Vector2f position);
        /**
         * @brief Destroy the Player object
         * 
         */
        ~Player();
        /**
         * @brief  UPDATE  the player.
         * 
         * @param deltaTime 
         */
        void update(sf::Time deltaTime);
        /**
         * @brief  draws the player to the screen.
         * 
         * @param target 
         */
        void draw(sf::RenderTarget &target);
        /**
         * @brief Get the Entity Type object
         * 
         * @return ENTITYTYPE 
         */
        ENTITYTYPE getEntityType() const;
        /**
         * @brief  Handles the player's input.
         * 
         * @param commands 
         * @param event 
         */
        void handleInput(CommandQueue& commands, sf::Event& event);
        /**
         * @brief  Handles the player's realtime input.
         * 
         * @param commands 
         */
        void handleRealtimeInput(CommandQueue& commands);
        /**
         * @brief  Checks if the player collides with another entity.
         * 
         */
        void onCollision();
        /**
         * @brief  shoot a bullet.
         * 
         */
        void shoot();
        /**
         * @brief Set the Player State object 
         * 
         * @param state 
         */
        void setPlayerState(PLAYERSTATE state);
        /**
         * @brief Set the Fuel Bar object
         * 
         */
        void setFuelBar();
        /**
         * @brief Set the Fuel object
         * 
         * @param fuel 
         */
        void setFuel(float fuel);
        /**
         * @brief Set the Lives object
         * 
         * @param lives 
         */
        void setLives(int lives);
        /**
         * @brief  Adds a humanoid to the player's vector of humanoids.
         * 
         * @param humanoid 
         */
        void addHumanoid(std::shared_ptr<Humanoid> humanoid);
        /**
         * @brief  Removes a humanoid from the player's vector of humanoids.
         * 
         * @param humanoid 
         */
        void removeHumanoid(std::shared_ptr<Humanoid> humanoid);
        /**
         * @brief Get the Humanoids Count object 
         * 
         * @return int 
         */
        int getHumanoidsCount() const;
        /**
         * @brief Get the Lives object
         * 
         * @return int 
         */
        int getLives() const;
        /**
         * @brief Get the Fuel object
         * 
         * @return float 
         */
        float getFuel() const;
        /**
         * @brief  draws the player's HUD to the screen.
         * 
         * @param target 
         */
        void drawHUD(sf::RenderTarget &target);
        /**
         * @brief Get the Player Position object
         * 
         * @return sf::Vector2f 
         */
        sf::Vector2f getPlayerPosition() const;
        /**
         * @brief Get the Bullets object
         * 
         * @return std::vector<std::unique_ptr<Projectile>>& 
         */
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