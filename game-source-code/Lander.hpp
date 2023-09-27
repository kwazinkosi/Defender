#ifndef LANDER_H
#define LANDER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Animation.hpp"
#include "Context.hpp" 
#include "Utills.hpp" 
#include "Projectile.hpp"
#include "Entity.hpp"
#include "CommandQueue.hpp"
#include "Context.hpp"

class Lander : public Entity
{
    public:
        Lander(Context& context);
        virtual ~Lander();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target);
        void update(sf::Time deltaTime, sf::Vector2f targetPosition);
        void onCollision();
        bool isStatic() const;
        bool collissionCheck(Entity* other);
        void move(float x, float y);
        sf::FloatRect getBounds() const;
        void OnDestroy();
        ENTITYTYPE getEntityType() const;
        void initLander();
        ENEMYSTATE getState() const;
        void setState(ENEMYSTATE state);
        void spawnPosition();
        void fireMissile();
        // Function to check if the Lander is alive
        bool isAlive() const;
        std::vector<std::unique_ptr<Projectile>>& getMissiles();

    private:
        void moveDown(sf::Time deltaTime);
        void moveUp(sf::Time deltaTime);
        void moveLeft(sf::Time deltaTime);
        void moveRight(sf::Time deltaTime);
        void updateMissiles(sf::Time deltaTime);
        Context *mContext;
        ENEMYSTATE enemyState; // Represents the state of the Lander (e.g., IDLE, MOVING, DEAD)
        sf::Sprite mLanderSprite;
        sf::Clock mLanderClock;
        sf::Clock mMissileTimer;
        sf::Time spawnTime;
        sf::Time fireTimer;
        sf::Texture texture; 
        float speed;
        bool canShoot;
        bool isActive;
        bool isDown;
        sf::Vector2f mTargetPosition;
        std::vector<std::unique_ptr<Projectile>> mMissiles;
        
        sf::Clock shootClock; // Clock for tracking shooting cooldown
};
#endif

