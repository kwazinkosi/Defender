#ifndef HUMANOID_HPP
#define HUMANOID_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include "Animation.hpp"
#include "Utills.hpp"
#include "Context.hpp"
#include "Entity.hpp"

class Humanoid: public Entity
{
    public:
        Humanoid(Context& context);
        ~Humanoid();
        
        // Functions
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target);
        void onCollision();
        ENTITYTYPE getEntityType() const;
        void setKidnapped(bool kidnapped);
        void setRescued(bool rescued);
        void setReleased(bool released);
        void setShotDown(bool shot);
        void setHumanoidPosition(float x, float y);
        void setAbductionSuccess(bool success);
        bool isKidnapped() const;
        bool isRescued() const;
        bool isReleased() const;
        bool isShotDown() const;
        sf::Vector2f getPosition() const;
        bool isAbductionSuccess() const;
        void OnDestroyAll();
        bool isDead() const;
        
    private:
        enum class State
        {
            IDLE = 0, MOVINGLEFT, MOVINGRIGHT, KIDNAPPED, RESCUED, RELEASED, COUNT
        };
        // Functions
        void initHumanoid();
        sf::Vector2f spawnPosition();
        void updatePosition(sf::Time deltaTime);
        void freeFall(sf::Time deltaTime);
        
        // Objects
        Context* mContext;
        // Variables
        sf::Clock mHumanoidClock;
        sf::Time mHumanoidTime;
        sf::Vector2f mPosition;
        State mCurrentAnimation;
        Animation animation[static_cast<int>(State::COUNT)]; // Array of spaceship animations
        bool mIsKidnapped;
        bool mIsRescued;
        bool mIsReleased;
        bool mIsAbductionSuccess;
        bool isShot;
        int direction;   // 0 = left, 1 = right
        float mDirectionTime;           
        float distance;
        const float mGravity = 981.f;
        bool mIsDead;
};

#endif // HUMANOID_HPP