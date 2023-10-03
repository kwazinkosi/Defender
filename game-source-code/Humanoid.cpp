#include "Humanoid.hpp"

Humanoid::Humanoid(Context& context)
    : Entity(100, 50.f, sf::Vector2f(0.f, 0.f), ENTITYTYPE::HUMANOID)
    , mContext(&context)
    , mIsKidnapped(false)
    , mIsRescued(false)
    , mIsReleased(false)
    , mIsAbductionSuccess(false)
    , isShot(false)
    , mIsDead(false)
{
    std::cout << "Humanoid constructor" << std::endl;
}