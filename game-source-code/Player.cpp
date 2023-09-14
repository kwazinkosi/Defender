#include "player.hpp"

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
            break;
        case PLAYERSTATE::MOVINGRIGHT:
            movement.x += mPlayerSpeed;
            break;
        case PLAYERSTATE::MOVINGLEFT:
            movement.x -= mPlayerSpeed;
            break;
        case PLAYERSTATE::MOVINGUP:
            movement.y -= mPlayerSpeed;
            break;
        case PLAYERSTATE::MOVINGDOWN:
            movement.y += mPlayerSpeed;
            break;
        case PLAYERSTATE::SHOOTING:
            //shoot();
            break;
        case PLAYERSTATE::DEAD:
            //to do
            break;
        default:
            break;
    }
    
    mPlayer.move( 2.f*movement * deltaTime.asSeconds());
    ScreenCollision();
    //mAnimator->update(deltaTime);
}

void Player::drawPlayer(sf::RenderWindow &window)
{
    window.draw(mPlayer);
}


void Player::onCollision(Collidable* other)
{
    if (other->getCollisionType() == "Enemy")
    {
        setPlayerState(PLAYERSTATE::DEAD);
    }
    else if(other->getCollisionType() == "EnemyBullet")
    {
        setPlayerState(PLAYERSTATE::DEAD);
    }
    else if(other->getCollisionType() == "PowerUp"){
        //do something
    }
    // TODO: Handle collision with other collidable objects

}

bool Player::isStatic() const
{
    return false;
}

std::string Player::getCollisionResponse() const
{
    return "Player";
}

void Player::addCollidable(std::shared_ptr<Collidable> collidable)
{
    collidables.push_back(collidable);
}

void Player::move(sf::Vector2f movement)
{
    mPlayer.move(movement*mPlayerSpeed);
}

void Player::switchPlayerAnimation(PLAYERSTATE state)
{
  //  mAnimator->playAnimation("MovingRight");
}

void Player::ScreenCollision()
{
    auto windowLeft = 0.f;
    auto windowUp = 0.f;
    auto windowRight = mContext->mWindow.getSize().x;
    auto windowDown = mContext->mWindow.getSize().y;
    if(mPlayer.getPosition().x  < 0.f) //left
    {
        mPlayer.setPosition(0.f, mPlayer.getPosition().y);
    }

    if(mPlayer.getPosition().y < 0.f) //up
    {
        mPlayer.setPosition(mPlayer.getPosition().x, 0.f);
    }
    if(mPlayer.getPosition().x + mPlayer.getGlobalBounds().width > windowRight) //right
    {
        mPlayer.setPosition(windowRight - mPlayer.getGlobalBounds().width, mPlayer.getPosition().y);
    }
    if(mPlayer.getPosition().y + mPlayer.getGlobalBounds().height > windowDown) //down
    {
        mPlayer.setPosition(mPlayer.getPosition().x, windowDown - mPlayer.getGlobalBounds().height);
    }
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
std::string Player::getCollisionType() const
{
    return "Player";
}

void Player::shoot()
{
}