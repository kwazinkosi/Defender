#ifndef HUMANOID_HPP
#define HUMANOID_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
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
        // Objects
        Context* mContext;
        // Variables
        sf::Vector2f mPosition;
        bool mIsKidnapped;
        bool mIsRescued;
        bool mIsReleased;
        bool mIsAbductionSuccess;
        bool isShot;
        int direction;   // 0 = left, 1 = right
        float mDirectionTime;           
        float distance;
        bool mIsDead;
};

#endif // HUMANOID_HPP