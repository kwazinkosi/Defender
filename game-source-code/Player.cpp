#include "player.hpp"

Player::Player(Context &context, sf::Vector2f position)
: Entity(100, 200.f, position, ENTITYTYPE::PLAYER)
, mPlayerState(PLAYERSTATE::IDLE)
, mContext(&context)
, mCommandQueue(nullptr)
, mFuelTimer(sf::Time::Zero)
, mPosition(position)
, mCurrentAnimation(Direction::IDLE)
, mPreviousAnimation(Direction::IDLE)
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
, mIsShipFlipped(false)
{
     this->initPlayer();
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
}

Player::~Player()
{
}
void Player::updateBullets(sf::Time deltaTime)
{
    for (size_t i = 0; i < mProjectiles.size(); i++)
    {
        mProjectiles[i]->update(deltaTime);
        if (mProjectiles[i]->isDestroyed())
        {
            mProjectiles.erase(mProjectiles.begin() + i);
        }
    }

    // remove projectiles that are out of bounds
    for (std::size_t i = 0; i < mProjectiles.size(); i++)
    {
        mProjectiles[i]->update(deltaTime);
        if ((mProjectiles[i]->getSprite().getPosition().x < 0) || (mProjectiles[i]->getSprite().getPosition().x > 800) || (mProjectiles[i]->getSprite().getPosition().y < 0) || (mProjectiles[i]->getSprite().getPosition().y > 600))
        {
            mProjectiles.erase(mProjectiles.begin() + i);
        }
    }
}

void Player::update(sf::Time deltaTime)
{
    if (!isDestroyed())
    {
        //std::cout << "Player::update() -- Updating player" << std::endl;
        resqueHumanoid(deltaTime);  
        updateInput(deltaTime);
        updateBullets(deltaTime);
        mAnimation[static_cast<int>(mCurrentAnimation)].update(deltaTime);
        setPosition(mAnimation[static_cast<int>(mCurrentAnimation)].getPosition());
        onCollision(); // check for collision with other entities
    }

    if (mCurrFuel <= 0.f)
    {
        mCurrFuel = 0.f;
        crashShip(deltaTime);
        isDestroyed();
    }
}

void Player::setPlayerState(PLAYERSTATE state)
{
    this->mPlayerState = state;
}

void Player::updateInput(sf::Time deltaTime)
{
    static int shootTimer = 0;
    while (!mCommandQueue->isEmpty())
    {
        Command command = mCommandQueue->pop();

        if (command.category == Category::Player)
        {
            if (command.action == Action::MoveLeft)
            {
                // std::cout << "Moving left : mMovementSpeed: " << mMovementSpeed << std::endl;
                mCurrentAnimation = Direction::LEFT;
                if(!isLeft)
                {
                    mCurrentAnimation = Direction::RIGHT;
                }
                moveLeft(deltaTime);
            }
            else if (command.action == Action::MoveRight)
            {
                // std::cout << "Moving right : mMovementSpeed: " << mMovementSpeed << std::endl;
                mCurrentAnimation = Direction::LEFT;
                if(!isLeft)
                {
                    mCurrentAnimation = Direction::RIGHT;
                }
                moveRight(deltaTime);
            }
            else if (command.action == Action::MoveUp)
            {
                // std::cout << "Moving up : mMovementSpeed: " << mMovementSpeed << std::endl;
                if(isLeft)
                {
                    mCurrentAnimation = Direction::UP;
                }
                else
                {
                    mCurrentAnimation = Direction::DOWN;
                }
                moveUp(deltaTime);
            }
            else if (command.action == Action::MoveDown)
            {
                // std::cout << "Moving down : mMovementSpeed: " << mMovementSpeed << std::endl;
                if(isLeft)
                {
                    mCurrentAnimation = Direction::UP;
                }
                else
                {
                    mCurrentAnimation = Direction::DOWN;
                }
                moveDown(deltaTime);
            }
            else if (command.action == Action::Shoot)
            {
                std::cout << "Player::update() -- Shooting." << std::endl;
                
                shootTimer++;
                if (shootTimer >= 5)
                {
                    shoot();
                    shootTimer = 0;
                }
            }
            else if (command.action == Action::FlipShip)
            {
                // std::cout << "Flipping ship." << std::endl;
                flipShip();
            }
            else
            {
                std::cout << "Player::update() -- Command action is not valid" << std::endl;
            }
        }
    }
}

void Player::moveLeft(sf::Time deltaTime)
{
    mPosition = getPosition();
    mPosition.x -= mMovementSpeed * deltaTime.asSeconds();
    mAnimation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
    mAnimation[static_cast<int>(mCurrentAnimation)].setPosition(mPosition);
    setPosition(mPosition);
    sprite.setPosition(mPosition);
}
void Player::moveRight(sf::Time deltaTime)
{
    mPosition = getPosition();
    mPosition.x += mMovementSpeed * deltaTime.asSeconds();
    mAnimation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
    mAnimation[static_cast<int>(mCurrentAnimation)].setPosition(mPosition);
    setPosition(mPosition);
    sprite.setPosition(mPosition);
}
void Player::moveDown(sf::Time deltaTime)
{
    mPosition = getPosition();
    mPosition.y += mMovementSpeed * deltaTime.asSeconds();
    mAnimation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
    mAnimation[static_cast<int>(mCurrentAnimation)].setPosition(mPosition);
    setPosition(mPosition);
}
void Player::moveUp(sf::Time deltaTime)
{
    mPosition = getPosition();
    mPosition.y -= mMovementSpeed * deltaTime.asSeconds();
    mAnimation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
    mAnimation[static_cast<int>(mCurrentAnimation)].setPosition(mPosition);
    setPosition(mPosition);
    sprite.setPosition(mPosition);
}

void Player::shoot(sf::Time deltaTime)
{
    auto bulletPos = mAnimation->getPosition();
    bulletPos.x += 30.f;
    bulletPos.y += 70.f;
    mProjectiles.push_back(std::make_unique<Projectile>(bulletPos, (isLeft ? sf::Vector2f(-1.f, 0) : sf::Vector2f(1.f, 0)), 300.f, ProjectileType::PlayerBullet));
}

void Player::draw(sf::RenderTarget &target)
{
    target.draw(mAnimation->getSprite());
    for (auto &bullet : mProjectiles)
    {
        target.draw(bullet->getSprite());
    }
}

void Player::handleInput(CommandQueue &commands, sf::Event &event)
{
    // Handle player input
    std::cout << "Player::handleInput() -- Handling player input" << std::endl;
    if (event.type == sf::Event::KeyReleased)
    {
        // flip spaceship
        if (event.key.code == sf::Keyboard::F)
        {
            std::cout << "Player::handleInput() -- Flipping spaceship" << std::endl;
            Command command(Action::FlipShip, Category::Player);
            commands.push(command);
        }
    }

    if(event.type == sf::Event::KeyPressed)
    {
        // if all 8 directions are pressed , decrease mCurrentfuel
        if ((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) || 
        (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) || 
        (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) ||
        (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S))
        {
            mCurrFuel -= mFuelBurnRate;
            setFuelBar();
        }
    }
    mCommandQueue = &commands; // set command queue pointer to commands passed in by reference
}

void Player::handleRealtimeInput(CommandQueue &commands)
{
    // Handle realtime input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // Move left
        Command command(Action::MoveLeft, Category::Player);
        commands.push(command);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        // Move right
        Command command(Action::MoveRight, Category::Player);
        commands.push(command);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        // Move up
        Command command(Action::MoveUp, Category::Player);
        commands.push(command);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        // Move down
        Command command(Action::MoveDown, Category::Player);
        commands.push(command);
    }
    // handle shooting
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        // Shoot
        Command command(Action::Shoot, Category::Player);
        commands.push(command);
    }

    mCommandQueue = &commands; // set command queue pointer to commands passed in by reference
}

void Player::onCollision()
{
    // handle collision with the screen
    screenCollision();
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
    // Set sprite
    sprite.setTextureRect(sf::IntRect(0, 0, 22, 6));
    sprite.setScale(4.f, 4.f);
    setPosition(mPosition);
    sprite.setTexture(texture);
    std::cout << "SpaceShip::initSpaceShip() -- Sprite set" << std::endl;
    // Set animations
    
    mAnimation[static_cast<int>(Direction::IDLE)] = Animation(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 2, sf::seconds(0.2f), true);
    mAnimation[static_cast<int>(Direction::UP)] =   Animation(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 3, sf::seconds(0.2f), true);
    mAnimation[static_cast<int>(Direction::DOWN)] = Animation(&texture, sf::Vector2i(0, 0), sf::Vector2i(22, 6), 3, sf::seconds(0.2f), true);
    mAnimation[static_cast<int>(Direction::RIGHT)]= Animation(&texture, sf::Vector2i(0, 0), sf::Vector2i(22, 6), 4, sf::seconds(0.2f), true);
    mAnimation[static_cast<int>(Direction::LEFT)] = Animation(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 4, sf::seconds(0.2f), true);
    // Set movement speed
    setMovementSpeed(100.f);
    std::cout << "SpaceShip::initSpaceShip() -- SpaceShip initialized" << std::endl;for (auto &animation : mAnimation)
    for(auto &animation : mAnimation)
    {
        animation.setScale(4.f, 4.f);
    }
    mAnimation[static_cast<int>(Direction::IDLE)].setPosition(mPosition);

}

void Player::setFuelBar()
{
    if (mCurrFuel <= 0.f)
    {
        mCurrFuel = 0.f;
    }
    
    mFuelBar.setSize(sf::Vector2f(mFuelBarBackground.getSize().x - 1.45*(mMaxFuel - mCurrFuel), mFuelBar.getSize().y));
}

void Player::setFuel(float fuel)
{
    mCurrFuel = fuel;
}

float Player::getFuel() const
{
    return mCurrFuel;
}

ENTITYTYPE Player::getEntityType() const
{
    return mEntityType;
}

void Player::shoot()
{
    auto bulletPos = mAnimation->getPosition();
    if (isLeft)
    {
        bulletPos.x += 10.f;
    }
    else
    {
        bulletPos.x += 88.f;
    }
    bulletPos.y += 18.f;
   
    mProjectiles.push_back(std::make_unique<Projectile>(bulletPos, (isLeft ? sf::Vector2f(-1.f, 0) : sf::Vector2f(1.f, 0)), 300.f, ProjectileType::PlayerBullet));
    
}

void Player::flipShip()
{
    std::cout << "Changing direction." << std::endl;
    isLeft = !isLeft;
    auto position = getPosition();
    mIsShipFlipped = !mIsShipFlipped;
    if (isLeft)
    {
        mCurrentAnimation = Direction::LEFT;
    }
    else
    {
        mCurrentAnimation = Direction::RIGHT;
    }
    mAnimation[static_cast<int>(mCurrentAnimation)].setPosition(position);
    setPosition(position);
}

void Player::drawHUD(sf::RenderTarget &target)
{
    target.draw(mFuelBarBackground);
    target.draw(mFuelBar);
    target.draw(mFuelBarText);
}

sf::Vector2f Player::getPlayerPosition() const
{
    return mAnimation->getPosition();
}

std::vector<std::unique_ptr<Projectile>> &Player::getBullets()
{
    return mProjectiles;
}

void Player::crashShip(sf::Time deltaTime)
{
    if (mCurrFuel <= 0.f)
    {
        mCurrFuel = 0.f;
        mAnimation->move(0.f, 100.f * deltaTime.asSeconds());
        if(mAnimation->getSprite().getPosition().y >= mContext->mBottomBound - mAnimation->getSprite().getGlobalBounds().height)
        {
            mAnimation->setPosition(sf::Vector2f(mAnimation->getPosition().x, mContext->mBottomBound - mAnimation->getSprite().getGlobalBounds().height));
            OnDestroy();
        }
    }
}

