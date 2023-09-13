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

void Player::ScreenCollision()
{
}

void Player::setPlayerState(PLAYERSTATE state)
{
    this->mPlayerState = state;
}

sf::FloatRect Player::getBoundingBox() const
{
}

sf::Vector2f Player::getPosition() const
{
}
void Player::setPosition(float x, float y)
{
}

void Player::shoot()
{
}