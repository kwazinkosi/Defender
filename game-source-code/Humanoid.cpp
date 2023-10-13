#include "Humanoid.hpp"

Humanoid::Humanoid(Context& context)
    : Entity(100, 50.f, sf::Vector2f(0.f, 0.f), ENTITYTYPE::HUMANOID)
    , mContext(&context)
    , mHumanoidTime(sf::Time::Zero)
    , mCurrentAnimation(State::IDLE)
    , mIsKidnapped(false)
    , mIsRescued(false)
    , mIsReleased(false)
    , mIsAbductionSuccess(false)
    , isShot(false)
    , mIsDead(false)
{
    std::cout << "Humanoid constructor" << std::endl;
    initHumanoid();
    mCurrentAnimation = State::IDLE;
}

Humanoid::~Humanoid()
{
    
}

void Humanoid::initHumanoid()
{
    std::cout << "Humanoid::initHumanoid() -- Initializing Humanoid" << std::endl;
    direction = rand() % 2; // 0 = left, 1 = right
    mHumanoidTime = sf::Time::Zero;
    mDirectionTime = rand() % 5 + 3.f;
    distance = (rand() % 50) * 4 + 50.f;
    // Load texture
    texture = mContext->mTextures->getResourceById(Textures::Humanoid);
    mCurrentAnimation = static_cast<State>(rand() % 2 + 1); // 1 = moving left, 2 = moving right
    sprite.setTextureRect(sf::IntRect(0, 0, 15, 32));
    mPosition = spawnPosition();
    setPosition(mPosition);
    sprite.setTexture(texture);
    // Set animations
    animation[static_cast<int>(State::IDLE)] = Animation(&texture, sf::Vector2i(0, 0), sf::Vector2i(15, 32), 1, sf::seconds(0.2f), true);
    animation[static_cast<int>(State::MOVINGRIGHT)] = Animation(&texture, sf::Vector2i(0, 0), sf::Vector2i(15, 32), 4, sf::seconds(0.3f), true);
    animation[static_cast<int>(State::MOVINGLEFT)] = Animation(&texture, sf::Vector2i(0, 0), sf::Vector2i(15, 32), 4, sf::seconds(0.3f), true);
    animation[static_cast<int>(State::KIDNAPPED)] = Animation(&texture, sf::Vector2i(0, 32), sf::Vector2i(15, 32), 4, sf::seconds(0.3f), true); 
    animation[static_cast<int>(State::RESCUED)] = Animation(&texture, sf::Vector2i(15, 32), sf::Vector2i(15, 32), 2, sf::seconds(0.3f), true);
    animation[static_cast<int>(State::RELEASED)] = Animation(&texture, sf::Vector2i(0, 32), sf::Vector2i(15, 32), 4, sf::seconds(0.3f), true);
    // Set movement speed
    setMovementSpeed((rand() % 25)*2 + 20.f); 
    std::cout << "Humanoid::initHumanoid() -- Humanoid initialized at position: " << getPosition().x << ", " << getPosition().y << std::endl;
    // Flip the MovingRight animation when moving left
    animation[static_cast<int>(State::MOVINGLEFT)].setScale(-0.7f, 1.f);
    animation[static_cast<int>(State::MOVINGLEFT)].setPosition(getPosition());
    animation[static_cast<int>(State::MOVINGRIGHT)].setScale(0.7f, 1.f);
    animation[static_cast<int>(State::IDLE)].setScale(0.7f, 1.f);
    animation[static_cast<int>(State::KIDNAPPED)].setScale(0.7f, 1.f);
    animation[static_cast<int>(State::RESCUED)].setScale(0.7f, 1.f);
    animation[static_cast<int>(State::RELEASED)].setScale(0.7f, 1.f);

}

sf::Vector2f Humanoid::spawnPosition()
{
    // Spawn at random position 
    auto multiplier = rand() % 4 + 1.f; 
    auto x = (rand() % 38)*5.f*multiplier + 20.f; // 38 * 5*4
    auto y = mContext->mBottomBound - 32.f - 10.f;

    //auto y = 700.f;
    auto position = sf::Vector2f(x, y);
    std::cout << "Humanoid::spawnPosition() -- Spawned at position: " << position.x << ", " << position.y << std::endl;
    std::cout << "Humanoid::spawnPosition() -- Bottom bound: " << mContext->mBottomBound << std::endl;
    return position;
}

void Humanoid::update(sf::Time deltaTime)
{
    updatePosition(deltaTime);
    animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
    animation[static_cast<int>(mCurrentAnimation)].update(deltaTime);
}

void Humanoid::draw(sf::RenderTarget& target)
{
    //std::cout<<"Humanoid::draw() -- Drawing Humanoid"<<std::endl;
    animation[static_cast<int>(mCurrentAnimation)].draw(target);
}

void Humanoid::updatePosition(sf::Time deltaTime)
{
    mHumanoidTime += deltaTime;
    auto distanceMoved = 0.f; // distance moved so far
    
    if (mHumanoidTime.asSeconds() >= mDirectionTime)
    {
        mHumanoidTime = sf::Time::Zero;
        direction = rand() % 2; // 0 = left, 1 = right
        distance = (rand() % 50)*4 + 50.f;
    }
    else 
    {
        if(!mIsKidnapped && !mIsRescued && !mIsReleased)
        {
            mCurrentAnimation = static_cast<State>(direction + 1);
            if (mCurrentAnimation == State::MOVINGLEFT)
            {
                if (mPosition.x <= 0.f || distanceMoved >= distance)
                {
                    direction = 1; // change direction to right
                    distance = (rand() % 50)*4 + 50.f;
                    distanceMoved = 0.f;
                }
                else
                {
                    // Keep moving left
                    mPosition.x -= mMovementSpeed * deltaTime.asSeconds();
                    distanceMoved += mMovementSpeed * deltaTime.asSeconds();
                }
            }
            else if (mCurrentAnimation == State::MOVINGRIGHT)
            {
                if (mPosition.x >= 768.f || distanceMoved >= distance)
                {
                    direction = 0; // change direction to left
                    distance = rand() % 50 + 50;
                    distanceMoved = 0.f;
                }
                else
                {
                    // Keep moving right
                    mPosition.x += mMovementSpeed * deltaTime.asSeconds();
                    distanceMoved += mMovementSpeed * deltaTime.asSeconds(); // distance moved so far
                }
            }
        }
        else if (mIsKidnapped)
        {
            mCurrentAnimation = State::KIDNAPPED;
        }
        else if (mIsRescued)
        {
            mCurrentAnimation = State::RESCUED;
        }
        else if (mIsReleased)
        {
            std::cout << "Humanoid::updatePosition() -- Released" << std::endl;
            mCurrentAnimation = State::RELEASED;
            freeFall(deltaTime);
        }
        animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
        sprite.setPosition(mPosition);
    }
}

void Humanoid::freeFall(sf::Time deltaTime)
{
    mPosition.y += 4.9f*mGravity* deltaTime.asSeconds() * deltaTime.asSeconds();
    animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
    sprite.setPosition(mPosition);
    // check if the humanoid has reached the ground   
}

void Humanoid::setKidnapped(bool kidnapped)
{
    //std::cout << "Humanoid::setKidnapped() -- Setting kidnapped to: " << (kidnapped ? "true" : "false") << std::endl;
    mIsKidnapped = kidnapped;
    if (mIsKidnapped)
    {
        mCurrentAnimation = State::KIDNAPPED;
    }
}

void Humanoid::setRescued(bool rescued)
{
    mIsRescued = rescued;
    if (mIsRescued)
    {
        mCurrentAnimation = State::RESCUED;
    }
}

void Humanoid::setReleased(bool released)
{
    mIsReleased = released;
    if (mIsReleased)
    {
        mCurrentAnimation = State::RELEASED;
    }
}

void Humanoid::setShotDown(bool shot)
{
    isShot = shot;
}

bool Humanoid::isKidnapped() const
{
    return mIsKidnapped;
}

bool Humanoid::isRescued() const
{
    return mIsRescued;
}

bool Humanoid::isReleased() const
{
    return mIsReleased;
}

bool Humanoid::isShotDown() const
{
    return isShot;
}

sf::Vector2f Humanoid::getPosition() const
{
    return mPosition;
}

bool Humanoid::isAbductionSuccess() const
{
    return mIsAbductionSuccess;
}

void Humanoid::setHumanoidPosition(float x, float y)
{
    mPosition.x = x;
    mPosition.y = y;
    sprite.setPosition(mPosition);
    animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
}

void Humanoid::setAbductionSuccess(bool success)
{
    mIsAbductionSuccess = success;
}

void Humanoid::OnDestroyAll()
{
    std::cout << "Humanoid::OnDestroyAll() -- Destroying all humanoid references" << std::endl;
    
    mIsDead = true;
}

bool Humanoid::isDead() const
{
    return mIsDead;
}

void Humanoid::onCollision()
{
    std::cout << "Humanoid::onCollision() -- Humanoid collided." << std::endl;
}

ENTITYTYPE Humanoid::getEntityType() const
{
    return ENTITYTYPE::HUMANOID;
}