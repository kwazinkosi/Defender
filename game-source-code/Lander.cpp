#include "Lander.hpp"

Lander::Lander(Context &context, sf::Vector2f position)
: Entity(100, 0.f, sf::Vector2f(0.f, 0.f), ENTITYTYPE::ENEMY)
, mContext(&context)
, enemyState(ENEMYSTATE::MOVINGDOWN)
, speed(50.f)
, canShoot(true)
, isActive(true)
, isDown(true)
, mKidnapping(false)
, mIsSeeking(false)
, mTargetPosition(position)
, mPosition(position)
, mCurrentAnimation(LANDERSTATE::IDLE)
{
    randDirX = float(rand() % 2);
    randSpeedX = rand() % int(speed) / 3;
    randSpeedY = rand() % int(speed) / 2 + speed / 2;
    directionTime = rand() % 1 + 2.f;
    mTargetHumanoid =std::make_shared<Humanoid>(context);
    std::cout << "Lander::Lander() -- Lander created." << std::endl;
    initLander();
    spawnTime = mLanderClock.getElapsedTime();
    fireTimer = mMissileTimer.getElapsedTime();
}
Lander::~Lander()
{
    std::cout << "Lander::~Lander() -- Lander destroyed." << std::endl;
}

void Lander::update(sf::Time deltaTime, sf::Vector2f playerPosition)
{
    if(!mIsSeeking)
    {   
        //std::cout << "Lander::update() -- Lander is not seeking -- Humanoid count: " << getHumanoidCount() << std::endl;
        initLanderState(); // Choose a random action to perform (0: Up, 1: Down, 2: Left, 3: Right, 4: seek humanoid)
    }
    mTargetPosition = playerPosition;
    std::cout << "Player is at: " << mTargetPosition.x << ", " << mTargetPosition.y << std::endl;
    sf::Vector2f landerPosition = getPosition();
    float targetDistance = std::sqrt(pow(mTargetPosition.x - landerPosition.x, 2) + pow(mTargetPosition.y - landerPosition.y, 2));
    updateMissiles(deltaTime);
   
    if ((targetDistance <= 200.f && mMissileTimer.getElapsedTime().asSeconds() >= 5.0f) && (!abductionInProgress()))
    {
        // engage the player
        fireMissile();
        mMissileTimer.restart(); 
    }

    // Handle movement based on the current state
    moveLander(deltaTime);
    // Update the animation based on the current state
    updateAnimation(deltaTime);
    // Update the kidnapping  
    updateKidnapping(deltaTime);
    // Check if the Lander is going out of the screen boundaries
    landerScreenCollision();
}

void Lander::initLander()
{
    texture = mContext->mTextures->getResourceById(Textures::Lander);
    std::cout << "size: " << texture.getSize().x/4 << " " << texture.getSize().y/2 << std::endl;

    // sprite.setPosition(100.0f, 100.0f); // Set an initial position (adjust as needed)
    sprite.setTextureRect(sf::IntRect(0, 0, 52, 48));
    sprite.setScale(0.7f, 0.7f);
    sprite.setTexture(texture);
    //sprite.setOrigin(getBounds().width / 2.f, getBounds().height / 2.f);
    setPosition(mPosition);
    //  Set animations
    animation[static_cast<int>(LANDERSTATE::IDLE)] = Animation(&texture, sf::Vector2i(0, 0), sf::Vector2i(52, 48), 4, sf::seconds(0.4f), true);
    animation[static_cast<int>(LANDERSTATE::MOVING)] = Animation(&texture, sf::Vector2i(0, 0), sf::Vector2i(52, 48), 4, sf::seconds(0.4f), true);
    animation[static_cast<int>(LANDERSTATE::KIDNAPPING)] = Animation(&texture, sf::Vector2i(0, 0), sf::Vector2i(52, 48), 4, sf::seconds(0.35f), true);
    // Set movement speed
    setMovementSpeed(50.f);
    std::cout << "Lander::initLander() -- Lander initialized at position: " << getPosition().x << ", " << getPosition().y << std::endl;
    spawnPosition();
    animation[static_cast<int>(LANDERSTATE::IDLE)].setScale(0.7f, 0.7f);
    animation[static_cast<int>(LANDERSTATE::MOVING)].setScale(0.7f, 0.7f);
    animation[static_cast<int>(LANDERSTATE::KIDNAPPING)].setScale(0.7f, 0.7f);
}

void Lander::addHumanoid(std::shared_ptr<Humanoid> human)
{
    if(human != nullptr)
    {
        mHumanoids.push_back(human);
    }
    else
    {
        std::cout << "Lander::addHumanoid() -- Humanoid is null." << std::endl;
    }
}

void Lander::removeHumanoid(std::shared_ptr<Humanoid> human)
{
    if(human != nullptr)
    {
        mHumanoids.erase(std::remove(mHumanoids.begin(), mHumanoids.end(), human), mHumanoids.end());
    }
    else
    {
        std::cout << "Lander::removeHumanoid() -- Humanoid is null." << std::endl;
    }
    std::cout << "Lander::removeHumanoid() -- Humanoids size: " << mHumanoids.size() << std::endl;
}

int Lander::getHumanoidCount() const
{
    return int(mHumanoids.size());
}

ENEMYSTATE Lander::getState() const
{
    return enemyState;
}

void Lander::setState(ENEMYSTATE state)
{
    enemyState = state;
}

void Lander::setTargetHumanoid(std::shared_ptr<Humanoid> human)
{
    mTargetHumanoid = human;
}

void Lander::setTargetPosition(sf::Vector2f position)
{
    mTargetPosition = position;

}

void Lander::setKidnapping(bool kidnapping)
{
    mKidnapping = kidnapping;
}

void Lander::spawnPosition()
{
    auto randX = (rand() % int ((mContext->mRightBound - getBounds().width)/5.f))*5.f;
    auto randY = rand() % int (mContext->mTopBound/4) - getBounds().height;
    mPosition.x = randX;
    mPosition.y = randY;
    setPosition(mPosition);
    animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
}

bool Lander::isAlive() const
{
    return isActive;
}

std::vector<std::unique_ptr<Projectile>>& Lander::getMissiles()
{
    return mMissiles;
}

void Lander::moveDown(sf::Time deltaTime)
{
    static sf::Time timeSinceLastMove = sf::Time::Zero;
    static sf::Clock moveClock;
    timeSinceLastMove += moveClock.restart();
    if (timeSinceLastMove.asSeconds() >= 1.f)
    {
        timeSinceLastMove = sf::Time::Zero;
        randDirX = rand() % 2;
        randSpeedX = (rand() % int(speed)) / 3;
        randSpeedY = (rand() % int(speed)) / 2 + speed / 2;
    }

    if (randDirX)
    {
        mPosition.y += randSpeedY*deltaTime.asSeconds();
        mPosition.x += randSpeedX*deltaTime.asSeconds();
    }
    else
    {
        mPosition.y += randSpeedY * deltaTime.asSeconds();
        mPosition.x -= randSpeedX * deltaTime.asSeconds();
    }
    setPosition(mPosition);
    animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);

    auto seekOrNot = rand() % 5;
    // if at 1/4 bottom of the screen, then seek
    if(mContext->mBottomBound - mPosition.y <= mContext->mBottomBound/4)
    {
        if (seekOrNot == 0)
        {
            moveRandom(deltaTime);
        }
        else
        {
            enemyState = ENEMYSTATE::SEEK;
        }
    }
}

void Lander::move(float x, float y)
{
    mPosition.x += x;
    mPosition.y += y;
    setPosition(mPosition);
    animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
}

void Lander::update(sf::Time deltaTime)
{

}

void Lander::updateAnimation(sf::Time deltaTime)
{
    if (mCurrentAnimation == LANDERSTATE::IDLE)
    {
        animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
        setPosition(mPosition);
        animation[static_cast<int>(mCurrentAnimation)].update(deltaTime);
        // start moving after 3 seconds
        static float timeSinceLastMove = 0.f;
        timeSinceLastMove += mLanderClock.restart().asSeconds();
        if (timeSinceLastMove >= 3.f)
        {
            mCurrentAnimation = LANDERSTATE::MOVING;
            timeSinceLastMove = 0.f;
        }
    }
    else if (mCurrentAnimation == LANDERSTATE::MOVING)
    {
        animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
        setPosition(mPosition);
        animation[static_cast<int>(mCurrentAnimation)].update(deltaTime);
    }
    else if (mCurrentAnimation == LANDERSTATE::KIDNAPPING)
    {
        animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
        setPosition(mPosition);
        animation[static_cast<int>(mCurrentAnimation)].update(deltaTime);
    }
}

void Lander::initLanderState()
{
    static sf::Time stateTime = sf::Time::Zero;
    static sf::Clock stateClock;
    stateTime += stateClock.restart();
    // Check if it's time to change direction
    if (stateTime.asSeconds() >= directionTime)
    {
        stateTime = sf::Time::Zero;
        directionTime = rand() % 2 + 1.f;
        if(!mHumanoids.empty() && (getPosition().y + getBounds().height < mContext->mBottomBound/2.f))
        {
            setState(ENEMYSTATE::SEEK);
        }
        else
        {
            moveRandom(stateTime); // move randomly
        }
        // Reset spawn time
        spawnTime = mLanderClock.getElapsedTime();
    }
}

void Lander::landerScreenCollision()
{
    const sf::Vector2f position = getPosition();
    if (position.x < mContext->mLeftBound)
    {
        // check if the lander is going out of the left bound
        setPosition(mContext->mLeftBound, position.y);
        setState(ENEMYSTATE::MOVINGRIGHT);
    }
    else if (position.x  > mContext->mRightBound - getBounds().width)
    {
        // check if the lander is going out of the right bound
        setPosition(mContext->mRightBound - getBounds().width, position.y);
        setState(ENEMYSTATE::MOVINGLEFT);
    }
    // if lander is going out of the top or bottom bound whilst kidnapping the humanoid, then kill the humanoid turn the lander around
    if (position.y < mContext->mTopBound - getBounds().height && mKidnapping)
    {
        // kill the humanoid
        std::cout << "Lander::landerScreenCollision() -- Lander is going out of the top bound whilst kidnapping the humanoid" << std::endl;
        mIsSeeking = false; // reset the seeking flag
        mTargetHumanoid->setKidnapped(false);
        mTargetHumanoid->setAbductionSuccess(true);
        mTargetHumanoid->OnDestroy(); // destroy the humanoid
        setPosition(position.x, mContext->mTopBound);
        setState(ENEMYSTATE::MOVINGUP);
        if (position.y < mContext->mTopBound - getBounds().height -50.f)
        {
            mKidnapping = false;
            // spawnPosition();
            setState(ENEMYSTATE::MOVINGDOWN);
        }
    }
    
    // =========================================================//
    else if (position.y < mContext->mTopBound && !mKidnapping) 
    {
        setPosition(position.x, mContext->mTopBound);
        setState(ENEMYSTATE::MOVINGDOWN);
    }
    else if (position.y > mContext->mBottomBound - getBounds().height)
    {
        setPosition(position.x, mContext->mBottomBound - getBounds().height);
        setState(ENEMYSTATE::MOVINGUP);
    }
}

void Lander::fireMissile()
 {
    sf::Vector2f playerPosition = mTargetPosition;
    sf::Vector2f landerPosition = getPosition();
    float distance = std::sqrt(pow(playerPosition.x - landerPosition.x, 2) + pow(playerPosition.y - landerPosition.y, 2));

    if (distance <= 200.f) {
        sf::Vector2f missilePosition = landerPosition;
        sf::Vector2f missileDirection = playerPosition - landerPosition;
        float missileSpeed = 250.f;

        // Normalize the missile direction vector
        static float length = std::sqrt(missileDirection.x * missileDirection.x + missileDirection.y * missileDirection.y);
        missileDirection.x /= length;
        missileDirection.y /= length;

        mMissiles.push_back(std::make_unique<Projectile>(missilePosition, missileDirection, missileSpeed, ProjectileType::Missile));
    }
}

void Lander::updateMissiles(sf::Time deltaTime)
{
    for (int i = 0; i < int(mMissiles.size()); i++)
    {
        mMissiles[i]->update(deltaTime);
        sf::Vector2f missilePosition = mMissiles[i]->getSprite().getPosition();
        // Check if the missile is out of bounds and remove it if necessary
        if (missilePosition.x < mContext->mLeftBound || missilePosition.x > mContext->mRightBound ||
            missilePosition.y < mContext->mTopBound || missilePosition.y > mContext->mBottomBound)
        {
            mMissiles.erase(mMissiles.begin() + i);
        }
    }
}

void Lander::onCollision()
{
    // isActive = false;
}

ENTITYTYPE Lander::getEntityType() const
{
    return mEntityType;
}

void Lander::OnDestroy()
{
    isActive = false;
    mDestroyed = true;
}

void Lander::moveLander(sf::Time deltaTime)
{
    if (enemyState == ENEMYSTATE::MOVINGDOWN)
    {
        moveDown(deltaTime);
    }
    else if (enemyState == ENEMYSTATE::MOVINGUP)
    {
        moveUp(deltaTime);
    }
    else if (enemyState == ENEMYSTATE::MOVINGLEFT)
    {
        moveLeft(deltaTime);
    }
    else if (enemyState == ENEMYSTATE::MOVINGRIGHT)
    {
        moveRight(deltaTime);
    }
    else if (enemyState == ENEMYSTATE::SEEK)
    {
        seekHumanoid(deltaTime);
    }
}

void Lander::moveRandom(sf::Time deltaTime)
{
    int randomDirection = rand() % 4; // 0: Up, 1: Down, 2: Left, 3: Right
    if (randomDirection == 0)
    {
        setState(ENEMYSTATE::MOVINGUP);
    }
    else if (randomDirection == 1)
    {
        setState(ENEMYSTATE::MOVINGDOWN);
    }
    else if (randomDirection == 2)
    {
        setState(ENEMYSTATE::MOVINGLEFT);
    }
    else if (randomDirection == 3)
    {
        setState(ENEMYSTATE::MOVINGRIGHT);
    }
}

void Lander::moveUp(sf::Time deltaTime)
{
    static sf::Time timeSinceLastMove = sf::Time::Zero;
    static sf::Clock moveClock;
    timeSinceLastMove += moveClock.restart();
    if (timeSinceLastMove.asSeconds() >= 1.f)
    {
        timeSinceLastMove = sf::Time::Zero;
        randDirX = rand() % 2;
        randSpeedX = (rand() % int(speed)) / 3;
        randSpeedY = (rand() % int(speed)) / 2 + speed / 2;
    }
    if (randDirX)
    {
        mPosition.x += randSpeedX * deltaTime.asSeconds();
        mPosition.y -= randSpeedY * deltaTime.asSeconds();
    }
    else
    {
        mPosition.x -= randSpeedX * deltaTime.asSeconds();
        mPosition.y -= randSpeedY * deltaTime.asSeconds();
    }
    setPosition(mPosition);
    animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
}

void Lander::moveLeft(sf::Time deltaTime)
{
    mPosition.x -= speed * deltaTime.asSeconds();
    setPosition(mPosition);
    animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
}

void Lander::moveRight(sf::Time deltaTime)
{
    mPosition.x += speed * deltaTime.asSeconds();
    setPosition(mPosition);
    animation[static_cast<int>(mCurrentAnimation)].move(mPosition.x, mPosition.y);
}

void Lander::draw(sf::RenderTarget &target)
{
    animation[static_cast<int>(mCurrentAnimation)].draw(target);
    //std::cout<<"Lander::draw() -- Lander drawn." << std::endl;
    for (auto &missile : mMissiles)
    {
        target.draw(missile->getSprite());
    }
}

bool Lander::abductionInProgress()
{
    if(!mHumanoids.empty())
    {
        for(auto &humanoid : mHumanoids)
        {
            if(humanoid->isKidnapped()  && getBounds().intersects(humanoid->getBounds()))
            {
                
                std::cout << "Lander::abductionInProgress() -- Abduction in progress." << std::endl;
                return true;
            }
        }
    }
    return false;
}

void Lander::updateKidnapping(sf::Time deltaTime)
{
    // if the Lander is closer to the player, then it should ingage and move towards the player and shoot
    if (getBounds().intersects(mTargetHumanoid->getBounds()) && !mTargetHumanoid->isKidnapped() &&
      !mKidnapping )
    {
        mKidnapping = true;
        mCurrentAnimation = LANDERSTATE::KIDNAPPING;
    }

    if (mKidnapping)
    {
        abductHumanoid(deltaTime);
    }
}

void Lander::abductHumanoid(sf::Time deltaTime)
{
    auto landerCenter = getCenter();
    mTargetHumanoid->setHumanoidPosition(landerCenter.x - mTargetHumanoid->getBounds().width / 2.f, landerCenter.y );
    mTargetHumanoid->setKidnapped(true);
    mTargetHumanoid->setReleased(false);
    mCurrentAnimation = LANDERSTATE::KIDNAPPING;
    // move up
    mPosition.y -= mMovementSpeed * deltaTime.asSeconds();
}

void Lander::dropHumanoid()
{
    if(mTargetHumanoid == nullptr|| mTargetHumanoid->isKidnapped() == false)
    {
        std::cout << "Lander::dropHumanoid() -- Target humanoid is null." << std::endl;
        return;
    }
    mKidnapping = false;
    mTargetHumanoid->setKidnapped(false);
    mTargetHumanoid->setReleased(true);
    mTargetHumanoid = nullptr;
    std::cout << "Lander::dropHumanoid() -- humanoids size: " << mHumanoids.size() << std::endl;
}

void Lander::seekHumanoid(sf::Time deltaTime)
{
    static  bool outOfRange = false;
    if(mHumanoids.empty())
    {
        return;
    }
    if (getBounds().intersects(mTargetHumanoid->getBounds()))
    {
        std::cout << "Lander::seekHumanoid() -- Lander has reached the humanoid" << std::endl;
        mCurrentAnimation = LANDERSTATE::KIDNAPPING;
        mKidnapping = true;
        return;
    }
    // move towards the humanoid
    auto humanoidPosition = getHumanoidPosition();
    auto distance =  humanoidPosition - getPosition();
    if(humanoidPosition == sf::Vector2f(-1.f, -1.f))
    {
        return;
    }
    // Check if out of range and update the outOfRange flag
    if (abs(distance.x) > rangeDistance && abs(distance.y) < rangeDistance)
    {
        outOfRange = true;
    }
    if (outOfRange || getPosition().y + getBounds().height >= 600.f)
    {
        static sf::Clock outOfRangeClock;
        //std::cout << "Lander::updateKidnapping() -- Lander is out of range -- time: " << outOfRangeClock.getElapsedTime().asSeconds() << std::endl;
        if (outOfRangeClock.getElapsedTime().asSeconds() >= rand() % 2 + 2.f) // wait for at least 2 seconds
        {
            // After waiting for 2 seconds, reset the flag and continue moving down
            outOfRange = false;
            outOfRangeClock.restart();
        } 
        else
        {
            // continue moving up
            mPosition.y -= mMovementSpeed/2.f * deltaTime.asSeconds();
        }
    }
    else
    {
        continueSeekingHumanoid(deltaTime, distance);
    }
}

sf::Vector2f Lander::getHumanoidPosition()
{
    static float timeSinceLastCheck = 0.f;
    static sf::Clock mTrackClock;
    static sf::Vector2f humanoidPosition = sf::Vector2f(-1.f, -1.f);
    
    timeSinceLastCheck += mTrackClock.restart().asSeconds();
    // std::cout << "Lander::getHumanoidPosition() -- timeSinceLastCheck: " << timeSinceLastCheck << std::endl;
    if(!mHumanoids.empty() && timeSinceLastCheck >= 2.f)
    {
        auto humanoidTarget = mHumanoids[0];
        for(auto &humanoid : mHumanoids)
        {
            // if not already kidnapped
            if(!humanoid->isKidnapped())
            {
                // if the current humanoid is closer to the lander than the previous one
                if(std::sqrt(pow(humanoid->getPosition().x - getPosition().x, 2) + pow(humanoid->getPosition().y - getPosition().y, 2)) < 
                    std::sqrt(pow(humanoidTarget->getPosition().x - getPosition().x, 2) + pow(humanoidTarget->getPosition().y - getPosition().y, 2)))
                {
                    humanoidTarget = humanoid;
                }
            }
        }
        mTargetHumanoid = humanoidTarget; // set the target humanoid
        humanoidPosition = humanoidTarget->getPosition();
        timeSinceLastCheck = 0.f;
    }
    // std::cout << "Lander::getHumanoidPosition() -- Humanoid position: " << humanoidPosition.x << ", " << humanoidPosition.y << std::endl;
    return humanoidPosition;
}

void Lander::continueSeekingHumanoid(sf::Time deltaTime, sf::Vector2f distance)
{
    mIsSeeking = true;
    //std::cout << "Lander::continueSeekingHumanoid() -- Lander is seeking the humanoid" << std::endl;
    static float acceleration = 1.f;
    
    // If in range and moving towards the target
    if (abs(distance.x) < 50.f && getPosition().y + getBounds().height < 600.f) {
        acceleration = 2.f; // Increase acceleration when close to the target
    }
    
    // Calculate the direction vector towards the humanoid
    sf::Vector2f direction = normalize(distance);
    
    // Calculate a desired position to move toward
    sf::Vector2f desiredPosition = getPosition() + direction * mMovementSpeed * acceleration * deltaTime.asSeconds();
    // Limit the lander's movement within screen boundaries
    desiredPosition.x = std::max(0.f, std::min(desiredPosition.x, 768.f));
    desiredPosition.y = std::max(0.f, std::min(desiredPosition.y, 600.f));
    auto posVector = getPosition();
    // Update the position based on interpolation
    mPosition = lerp(posVector, desiredPosition, 0.5f); // Adjust the interpolation factor as needed
    // Set the updated position to the sprite
    sprite.setPosition(mPosition);
}

sf::Vector2f Lander::normalize(sf::Vector2f &vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        vector.x /= length;
        vector.y /= length;
    }
    return vector;
}

sf::Vector2f Lander::lerp(sf::Vector2f &vector, const sf::Vector2f &target, float speed)
{
    vector.x += (target.x - vector.x) * speed;
    vector.y += (target.y - vector.y) * speed;
    return vector;
}