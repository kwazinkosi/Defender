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
    texture = mContext->mTextures->getResourceById(Textures::Humanoid);
    // Set sprite
    sprite.setTextureRect(sf::IntRect(0, 0, 15, 32));
    sprite.setTexture(texture);
    //sprite.setOrigin(getBounds().width / 2.f, getBounds().height / 2.f);
    mPosition = spawnPosition();
    setPosition(mPosition);
    // Set movement speed
    setMovementSpeed((rand() % 25)*2 + 20.f); 
}
sf::Vector2f Humanoid::spawnPosition()
{

}
