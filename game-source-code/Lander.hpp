#ifndef LANDER_H
#define LANDER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include "Animation.hpp"
#include "Context.hpp" 
#include "Utills.hpp" 
#include "Projectile.hpp"
#include "Entity.hpp"
#include "CommandQueue.hpp"
#include "Humanoid"

enum class LANDERSTATE
{
    IDLE = 0, MOVING, KIDNAPPING, COUNT
};
class Lander : public Entity
{
    public:
        Lander(Context& context, sf::Vector2f position);

        virtual ~Lander();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target);
        void onCollision();
        void move(float x, float y);
        void OnDestroy();
        ENTITYTYPE getEntityType() const;

        void update(sf::Time deltaTime, sf::Vector2f targetPosition);
        void initLander();
        void addHumanoid(std::shared_ptr<Humanoid> human);
        void removeHumanoid(std::shared_ptr<Humanoid> human);
        void dropHumanoid();
        int getHumanoidCount() const;
        ENEMYSTATE getState() const;
        void setState(ENEMYSTATE state);
        void setTargetHumanoid(std::shared_ptr<Humanoid> human);
        void setTargetPosition(sf::Vector2f position);
        void setKidnapping(bool kidnapping);
        void spawnPosition();
        void fireMissile();
        bool isAlive() const;
        std::vector<std::unique_ptr<Projectile>>& getMissiles();

    private:
        // Functions
        void initLanderState();
        void landerScreenCollision();
        void moveLander(sf::Time deltaTime);
        void moveDown(sf::Time deltaTime);
        void moveUp(sf::Time deltaTime);
        void moveLeft(sf::Time deltaTime);
        void moveRight(sf::Time deltaTime);
        void moveRandom(sf::Time deltaTime);
        void updateMissiles(sf::Time deltaTime);
        sf::Vector2f getHumanoidPosition();
        void updateAnimation(sf::Time deltaTime);
        void updateKidnapping(sf::Time deltaTime);
        void seekHumanoid(sf::Time deltaTime);
        void continueSeekingHumanoid(sf::Time deltaTime, sf::Vector2f distance);
        void abductHumanoid(sf::Time deltaTime);
        bool abductionInProgress();
        sf::Vector2f normalize(sf::Vector2f& vector);
        sf::Vector2f lerp (sf::Vector2f &vector, const sf::Vector2f &target, float speed);
        Context *mContext;
        std::vector<std::shared_ptr<Humanoid>> mHumanoids;
        std::shared_ptr<Humanoid> mTargetHumanoid;
        ENEMYSTATE enemyState; // Represents the state of the Lander (e.g., IDLE, MOVING, DEAD)
        sf::Clock mLanderClock;
        sf::Clock mMissileTimer;
        sf::Time spawnTime;
        sf::Time fireTimer;
        sf::Texture texture; 
        float speed;
        bool canShoot;
        bool isActive;
        bool isDown;
        bool mKidnapping;
        bool mIsSeeking;
        sf::Vector2f mTargetPosition;
        sf::Vector2f mPosition;
        std::vector<std::unique_ptr<Projectile>> mMissiles;

        sf::Clock mSeekClock;
        sf::Time mLanderTime;
        LANDERSTATE mCurrentAnimation;
        Animation animation[static_cast<int>(LANDERSTATE::COUNT)]; // Array of spaceship animations;
        
        sf::Clock shootClock; // Clock for tracking shooting cooldown
        float rangeDistance; // Distance from player to Lander
        float randDirX;
        float randSpeedX;
        float randSpeedY;
        float directionTime;
};
#endif

