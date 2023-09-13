#include "Player.hpp"

Player::Player(Context &context) : 
    mContext(&context),
    mPlayerState(PLAYERSTATE::IDLE)
{
    mPlayer.setSize(sf::Vector2f(50.f,50.f));
    mPlayer.setFillColor(sf::Color::Green);
    mPlayer.setPosition(100.f, 100.f);
}

Player::~Player()
{
}

void Player::update(sf::Time deltaTime)
{   
    
    sf::Vector2f movement(0.f, 0.f);

    switch (mPlayerState)
    {
        case PLAYERSTATE::IDLE:
            //mAnimator->playAnimation("Idle");
            //mAnimator->update(deltaTime);
            break;
        case PLAYERSTATE::MOVINGRIGHT:
            movement.x += mPlayerSpeed;
            //mAnimator->playAnimation("MovingRight");
            //mAnimator->update(deltaTime);
            break;
        case PLAYERSTATE::MOVINGLEFT:
            movement.x -= mPlayerSpeed;
            //mAnimator->playAnimation("MovingLeft");
            //mAnimator->update(deltaTime);
            break;
        case PLAYERSTATE::MOVINGUP:
            movement.y -= mPlayerSpeed;
            //mAnimator->playAnimation("MovingUp");
            //mAnimator->update(deltaTime);
            break;
        case PLAYERSTATE::MOVINGDOWN:
            movement.y += mPlayerSpeed;
            //mAnimator->playAnimation("MovingDown");
            //mAnimator->update(deltaTime);
            break;
        case PLAYERSTATE::SHOOTING:
            //shoot();
            break;
        case PLAYERSTATE::DEAD:
            //do something
            break;
        default:
            break;
    }
    
    mPlayer.move( 2.f*movement * deltaTime.asSeconds());
    //mAnimator->update(deltaTime);
}

void Player::drawPlayer(sf::RenderWindow &window)
{
    window.draw(mPlayer);
}

bool Player::isStatic() const
{
    return false;
}

void Player::move(sf::Vector2f movement)
{
    mPlayer.move(movement*mPlayerSpeed);
}

void Player::setPlayerState(PLAYERSTATE state)
{
    this->mPlayerState = state;
}

sf::FloatRect Player::getBoundingBox() const
{
    return mPlayer.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const
{
    return mPlayer.getPosition();
}
void Player::setPosition(float x, float y)
{
     mPlayer.setPosition(x, y);
}

void Player::shoot()
{

}