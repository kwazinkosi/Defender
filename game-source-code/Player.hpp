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



class Player: public Collidable
{
    public:
        Player(Context &context, sf::Vector2f position);
        ~Player();
        virtual void update(sf::Time deltaTime);
        virtual void draw(sf::RenderTarget &target);
        void handleInput(CommandQueue& commands, sf::Event& event);
        void handleRealtimeInput(CommandQueue& commands);
        virtual void onCollision();
        sf::FloatRect getBounds() const;
        virtual bool isStatic() const;
        virtual bool collissionCheck(Entity* other);
        virtual void move(float x, float y);
        virtual void OnDestroy();
        virtual ENTITYTYPE getEntityType() const;

        void addCollidable(std::shared_ptr<Entity> collidable);
        void shoot();
        void setPlayerState(PLAYERSTATE state);
        void setAnimation(Command command, bool &isHorizontalAccelerating);
        void setFuelBar();
        void setFuel(float fuel);
        float getFuel();
        void drawHUD(sf::RenderTarget &target);
        sf::Vector2f getPlayerPosition() const;
        std::vector<std::unique_ptr<Projectile>>& getBullets();

    private:
        void moveLeft(sf::Time deltaTime);
        void moveRight(sf::Time deltaTime);
        void moveUp(sf::Time deltaTime);
        void moveDown( sf::Time deltaTime);
        void shoot(sf::Time deltaTime);
        //void screenWrap();
        void screenCollision();
        void initPlayer();
        void flipShip();
        void crashShip(sf::Time deltaTime);
        void updateInput(sf::Time deltaTime);
        void updateBullets(sf::Time deltaTime);
        std::vector<std::unique_ptr<Entity>> collidables; // List of collidables that the player can collide with, unique_ptr because we want to transfer ownership of the collidable objects to the player.
        PLAYERSTATE mPlayerState;
        Context *mContext;
        CommandQueue *mCommandQueue;
        std::vector<std::unique_ptr<Projectile>> mProjectiles; // This is the vector that will hold all the projectiles that the player shoots out.
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
        sf::Text mFuelBarText;
        sf::Vector2f mScale;
        sf::Clock mPlayerClock; 
        sf::Time mFuelTimer;
        sf::RectangleShape mFuelBar;
        sf::RectangleShape mFuelBarBackground;
        sf::Vector2f mPosition;
};

#endif //PLAYER_H