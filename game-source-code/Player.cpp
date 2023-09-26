#include "player.hpp"

Player::Player(Context &context, sf::Vector2f position)
: Entity(100, 200.f, position, ENTITYTYPE::PLAYER)
, mPlayerState(PLAYERSTATE::IDLE)
, mContext(&context)
, mCommandQueue(nullptr)
, mLeftBound(context.mWorldView.getCenter().x - context.mWorldView.getSize().x / 2.f)
, mRightBound(context.mWorldView.getCenter().x + context.mWorldView.getSize().x / 2.f)
, mTopBound(context.mWorldView.getCenter().y - context.mWorldView.getSize().y / 2.f)
, mBottomBound(context.mWorldView.getCenter().y + context.mWorldView.getSize().y / 2.f)
, mLives(3)
, isLeft(true)
, isSetDefault(false)
, isSetAccelerate(false)
, mCurrFuel(float(getHealth()))
, mMaxFuel(100.f)
, mFuelBurnRate(0.1f)
, mFuelTimer(sf::Time::Zero)
{
    this->initPlayer();
    mAnimation = std::make_unique<Animation>(&texture, position, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    mFuelBarText = sf::Text("Fuel: ", context.mFonts->getResourceById(Fonts::GamePlayed), 16);
    mFuelBarText.setPosition(sf::Vector2f((mContext->mHudView.getCenter().x - mContext->mHudView.getSize().x / 2.f) + 5.f, mContext->mHudView.getCenter().y - mContext->mHudView.getSize().y / 2.f + 11.f));
    mFuelBarText.setFillColor(sf::Color::Yellow);
    
    mFuelBarBackground.setFillColor(sf::Color::White);
    mFuelBarBackground.setSize(sf::Vector2f(mContext->mHudView.getSize().x -55.f, 16.f));
    mFuelBarBackground.setPosition(sf::Vector2f((mContext->mHudView.getCenter().x - mContext->mHudView.getSize().x / 2.f )+55.f, mContext->mHudView.getCenter().y - mContext->mHudView.getSize().y / 2.f + 10.f));
    

    mFuelBar.setFillColor(sf::Color::Green);
    mFuelBar.setSize(sf::Vector2f(mContext->mHudView.getSize().x -55.f, 12.f));
    mFuelBar.setPosition(sf::Vector2f((mContext->mHudView.getCenter().x - mContext->mHudView.getSize().x / 2.f)+55.f, mContext->mHudView.getCenter().y - mContext->mHudView.getSize().y / 2.f + 12.f));
    std::cout << "Player::Player() -- Player created." << std::endl;
    std::cout<< "Bar size: " << mFuelBar.getSize().x << std::endl;
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

void Player::updateInput(sf::Time deltaTime)
{
}

void Player::moveLeft(sf::Time deltaTime)
{
    mAnimation->move(-mMovementSpeed * deltaTime.asSeconds(), 0.f);
}
void Player::moveRight(sf::Time deltaTime)
{
    
    mAnimation->move(mMovementSpeed * deltaTime.asSeconds(), 0.f);
}
void Player::moveDown(sf::Time deltaTime)
{
    mAnimation->move(0.f, mMovementSpeed * deltaTime.asSeconds());
}
void Player::moveUp(sf::Time deltaTime)
{
    mAnimation->move(0.f, -mMovementSpeed * deltaTime.asSeconds());
}

void Player::shoot(sf::Time deltaTime)
{
    auto bulletPos = mAnimation->getPosition();
    bulletPos.x += 30.f;
    bulletPos.y += 70.f;
    mProjectiles.push_back(std::make_unique<Projectile>(bulletPos, (isLeft ? sf::Vector2f(-1.f, 0) : sf::Vector2f(1.f, 0)), 300.f, ProjectileType::PlayerBullet));
}


void Player::screenCollision()
{
    if (mAnimation->getPosition().x < mLeftBound)
    {
        mAnimation->setPosition(sf::Vector2f(mLeftBound, mAnimation->getPosition().y));
    }
    else if (mAnimation->getPosition().x > mRightBound - mAnimation->getSprite().getGlobalBounds().width)
    {
         mAnimation->setPosition(sf::Vector2f(mRightBound- mAnimation->getSprite().getGlobalBounds().width, mAnimation->getPosition().y));
    }
    
    if (mAnimation->getPosition().y < mTopBound)
    {
         mAnimation->setPosition(sf::Vector2f(mAnimation->getPosition().x, mTopBound));
    }
    else if (mAnimation->getPosition().y > mBottomBound - mAnimation->getSprite().getGlobalBounds().height)
    {
        mAnimation->setPosition(sf::Vector2f(mAnimation->getPosition().x, mBottomBound - mAnimation->getSprite().getGlobalBounds().height));
    }
}

void Player::initPlayer()
{
    texture = mContext->mTextures->getResourceById(Textures::Player);
    sprite.setTexture(texture);
    this->sprite.setTextureRect(sf::IntRect(0, 6, 22, 6)); // to fix
    this->sprite.setScale(2.f, 2.f);
    this->sprite.setPosition(400.f, 300.f);
    this->sprite.setTexture(this->texture);
    mMovementSpeed = 100.f;
    mCollisionType = CollisionType::Player;
}