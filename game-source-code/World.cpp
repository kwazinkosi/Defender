#include "World.hpp"

World::World(Context &context)
: mCommandQueue(nullptr)
, mStarGenerator(nullptr)
, mSpaceship(nullptr)
, mMountains(nullptr)
, mContext(&context)
, mWindow(&context.mWindow)
, mWorldView(&context.mWorldView)
, mMiniMapView(&context.mMiniMapView)
, mWorldBounds(0.f, 0.f, 2000.f, context.mWorldView.getSize().y) // spawn position is at middle of the screen
, mPlayerSpawnPosition(context.mWorldView.getSize().x / 2.f, context.mWorldView.getSize().y / 2.f)
, mScrollSpeed(0.f)
{
    try
    {
        std::cout << "World::World() - Creating the world" << std::endl;
        loadTextures();
        //initHumanoids();
        std::cout << "World::World() - Creating enemies" << std::endl;
        initEnemies();
        std::cout << "World::World() - Creating layers" << std::endl;
        auto posY = context.mWorldView.getSize().y; // == groundPos
        std::cout << "World::World() - Creating command queue" << std::endl;
        mCommandQueue = std::make_shared<CommandQueue>();
        std::cout << "World::World() - Creating star generator" << std::endl;
        mStarGenerator = std::make_unique<StarGenerator>(context);
        std::cout << "World::World() - Creating player" << std::endl;
        mSpaceship = std::make_unique<Player>(*mContext, mPlayerSpawnPosition);
        //addEntity(std::move(mSpaceship));
        std::cout << "World::World() - Creating mountains" << std::endl;
        mMountains = std::make_unique<Mountains>(context, true, 100.f, posY);
        initpowerUps();
        std::cout << "World::World() - World created" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "World::World() - Exception: " << e.what() << std::endl;
        throw; // re-throw the exception to terminate the program
    }
}

void World::loadTextures()
{
    mMountainSprite.setTexture(mContext->mBackgrounds->getResourceById(Backgrounds::Mountains));
    std::cout << "World::loadTextures - Loaded Resources/textures/mountains.png" << std::endl;
    // Set texture to repeat
    mMountainTexture.setRepeated(true);
}

void World::initEnemies()
{
    // 3 landers for now
    for (int i = 0; i < 3; i++)
    {
        std::cout << "World::initEnemies() - Creating lander" << std::endl;
        auto lander = std::make_unique<Lander>(*mContext); 
        mLanders.push_back(std::move(lander));
    }

    // Add landers to the player's collidable list
}
void World::initpowerUps()
{
    std::cout << "World::initpowerUps() - Creating powerUp" << std::endl;
    auto position = sf::Vector2f(float(rand() % int(mContext->mRightBound -50)), mContext->mBottomBound- 50);

    auto powerUp = std::make_unique<PowerUp>(*mContext, position);
    mPowerUps.push_back(std::move(powerUp));
}


void World::handleInput(CommandQueue &commands, sf::Event &event)
{
    // Handle player input
    mSpaceship->handleInput(commands, event);
}

void World::handleRealtimeInput(CommandQueue &commands)
{
    // Handle player realtime input
    mSpaceship->handleRealtimeInput(commands);
}
std::pair<bool, int> World::update(sf::Time deltaTime)
{
    // mWorldView->move(-100.f * deltaTime.asSeconds(), 0.f);
    // Update star generator
     //std::cout << "World::update() - Updating star generator" << std::endl;
    mStarGenerator->update(deltaTime);
    // std::cout << "World::update() - Updating mountains" << std::endl;
    mMountains->update(deltaTime);
    // Update player
    // std::cout << "World::update() - Updating player" << std::endl;
    mSpaceship->update(deltaTime);
    // update powerUps
    updatePowerUps(deltaTime);
    // update Enemies
    // std::cout << "World::update() - Updating enemies" << std::endl;
    updateEnemies(deltaTime);
    onCollission();
    updateCollisions();
    // Check if game is over
    auto gameOverResult = gameOver();
    // std::cout << "World::update() - Game over result: " << gameOverResult.first << std::endl;
    return gameOverResult;
}
void World::updateEnemies(sf::Time deltaTime)
{
    //std::cout << "World::updateEnemies() - Updating enemies | player position: " << mSpaceship->getPlayerPosition().x << ", " << mSpaceship->getPlayerPosition().y << std::endl;
    // std::cout << "World::updateEnemies() - mLanders.size() = " << mLanders.size() << std::endl;
    for (auto &lander : mLanders)
    {
        // update lander
    }
}

void World::updatePowerUps(sf::Time deltaTime)
{
    sf::Clock clock;
    auto spawnTime =sf::Time::Zero;
    static auto prevTime = spawnTime;

    for (auto &powerUp : mPowerUps)
    {
        powerUp->update(deltaTime);
    }

    spawnTime += clock.restart();
    //std::cout << "World::updatePowerUps() - spawnTime: " << spawnTime.asSeconds() << std::endl;
    //std::cout << "World::updatePowerUps() - prevTime: " << prevTime.asSeconds() << std::endl;

    if(mPowerUps.empty())
    {
        prevTime +=clock.restart();

        if(prevTime >= sf::seconds(3.f))
        {
            initpowerUps();
            prevTime = sf::Time::Zero;
            spawnTime = sf::Time::Zero;
        }
    } 
}

void World::render()
{
    //mWorldView->setViewport(mContext->mWorldView.getViewport());
    mWindow->setView(*mWorldView);
    // Draw on world view
    drawView(*mWorldView);
    mWindow->draw(mContext->mWorldRect);
    // Set minimap view
    mWindow->setView(*mMiniMapView);
    // Draw on minimap view
    mWindow->draw(mContext->mMapRect);
    //
    // Set hud view
    mWindow->setView(mContext->mHudView);
    // Draw on hud view
    mWindow->draw(mContext->mHudRect);
    mSpaceship->drawHUD(*mWindow);

}

void World::drawView(sf::View &view)
{
    // Draw background
    mWindow->draw(mBackground);
    // Draw stars
    mStarGenerator->draw(*mWindow);
    // Draw mountains
    mMountains->draw(*mWindow);
    //Draw enemies
    mSpaceship->draw(*mWindow);
}

void World::drawEnemies(sf::RenderTarget &target)
{
    for (auto &lander : mLanders)
    {
    }
}

void World::drawPowerUps(sf::RenderTarget &target)
{
    for (auto &powerUp : mPowerUps)
    {
        powerUp->draw(target);
    }
}


void World::onCollission()
{

}

void World::updateCollisions()
{

}

std::pair<bool, int> World::gameOver() const
{

}