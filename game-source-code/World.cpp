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
        initHumanoids();
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
        mHighScoreManager = std::make_unique<HighScoreManager>();

        initAsteroid();
        // Add humanoids to the player's abductable humanoids list
        for (auto &humanoid : mHumanoids)
        {
            mSpaceship->addHumanoid(humanoid);
            for(auto &lander : mLanders)
            {
                lander->addHumanoid(humanoid);
            }
        }
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
        auto lander = std::make_unique<Lander>(*mContext, sf::Vector2f(0.f, 0.f)); 
        mLanders.push_back(std::move(lander));
    }
    // Add landers to the player's collidable list
}
sf::Vector2f World::SpawnPosition()
{
    sf::Vector2f position;
    position.x = rand() % int(mContext->mWorldView.getSize().x);
    position.y = ((mContext->mWorldView.getCenter().y - mContext->mWorldView.getSize().y / 2.f) - 100.f);
    if(position.x < 50.f)
    {
        position.x = 50.f;
    }
    if(position.x > mContext->mWorldView.getSize().x - 50.f)
    {
        position.x = mContext->mWorldView.getSize().x - 50.f;
    }
    return position;
}
void World::initAsteroid()
{
    //std::cout << "World::initEnemies() - Creating Asteroid" << std::endl;
    // Asteroid position should start at the top of the screen
    
    for (int i = 0; i < 3; i++)
    {
        auto position = SpawnPosition();
        auto asteroid = std::make_unique<Asteroid>(*mContext, position);
        mAsteroids.push_back(std::move(asteroid));
    }
    std::cout<<"World::initAsteroid() - Asteroid created"<<std::endl;

    // clear asteroids beyond the bottom screen
         
    std::cout << "world::initAsteroid() - Done clearing asteroids" << std::endl;
}
void World::initpowerUps()
{
    std::cout << "World::initpowerUps() - Creating powerUp" << std::endl;
    auto position = sf::Vector2f(float(rand() % int(mContext->mRightBound -50)), mContext->mBottomBound- 50);

    auto powerUp = std::make_unique<PowerUp>(*mContext, position);
    mPowerUps.push_back(std::move(powerUp));
}

void World::initHumanoids()
{
    auto maxHumanoids = rand() % 5 + 5; // 5 to 10 humanoids
    for (int i = 0; i < maxHumanoids; i++)
    {
        auto humanoid = std::make_shared<Humanoid>(*mContext);
        std::cout << "World::initHumanoids() - Adding humanoid to mHumanoids" << std::endl;
        std::cout <<"left: "<< mContext->mLeftBound << " right: " << mContext->mRightBound << "| top: " << mContext->mTopBound << " bottom: " << mContext->mBottomBound << std::endl;
        mHumanoids.push_back(std::move(humanoid));
    }
    // Add humanoids to the player's collidable list
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
Data World::update(sf::Time deltaTime)
{
    // mWorldView->move(-100.f * deltaTime.asSeconds(), 0.f);
    // Update star generator
     //std::cout << "World::update() - Updating star generator" << std::endl;
    mStarGenerator->update(deltaTime);
    // std::cout << "World::update() - Updating mountains" << std::endl;
    mMountains->update(deltaTime);
    // Update player
    updateHumanoids(deltaTime);
    // std::cout << "World::update() - Updating player" << std::endl;
    mSpaceship->update(deltaTime);
    // update powerUps
    updatePowerUps(deltaTime);
    // update Enemies
    // std::cout << "World::update() - Updating enemies" << std::endl;
    updateEnemies(deltaTime);
    updateAsteroids(deltaTime);
    onCollission();
    updateCollisions();
    mContext->mScore.setScoreText(mContext->mFonts->getResourceById(Fonts::GamePlayed));
    
    // Check if game is over
    auto gameOverResult = gameOver();
    // std::cout << "World::update() - Game over result: " << gameOverResult.first << std::endl;
    return gameOverResult;
}
void World::updateEnemies(sf::Time deltaTime)
{
    for (auto &lander : mLanders)
    {
        // std::cout << "World::updateEnemies() - Updating lander" << std::endl;
        lander->update(deltaTime, mSpaceship->getCenter());
        // Check if lander is collides with player bullets
    }
}

void World::updateAsteroids(sf::Time deltaTime)
{
    for (auto &asteroid : mAsteroids)
    {
        asteroid->update(deltaTime);
    }
    //std::cout << "Asteroids left: " << mAsteroids.size() << std::endl;   
    if(mAsteroids.empty())
    {
        initAsteroid();
    }   

    if(mAsteroids.size() < 3)
    {
        auto position = SpawnPosition();
        auto asteroid = std::make_unique<Asteroid>(*mContext, position);
        mAsteroids.push_back(std::move(asteroid));
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
void World::updateHumanoids(sf::Time deltaTime)
{
   for (auto &humanoid : mHumanoids)
    {
        humanoid->update(deltaTime);
        // Check if humanoid is collides with player bullets
        if(humanoid->isDestroyed())
        {
            std::cout << "World::updateHumanoids() - Humanoid destroyed- erase it on the onCollission() method" << std::endl;
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
    // Set hud view
    mWindow->setView(mContext->mHudView);
    // Draw on hud view
    mWindow->draw(mContext->mHudRect);
    mSpaceship->drawHUD(*mWindow);
    mContext->mScore.drawScore(*mWindow);

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
    drawEnemies(*mWindow);
    // Draw asteroids
    drawAsteroids(*mWindow);
    // Draw humanoids
    drawHumanoids(*mWindow);
    // Draw powerUps
    drawPowerUps(*mWindow);
    // Draw player
    mSpaceship->draw(*mWindow);
}

void World::drawEnemies(sf::RenderTarget &target)
{
    for (auto &lander : mLanders)
    {
        lander->draw(target);
    }
}

void World::drawAsteroids(sf::RenderTarget &target)
{
    for (auto &asteroid : mAsteroids)
    {
        asteroid->draw(target);
    }
}

void World::drawPowerUps(sf::RenderTarget &target)
{
    for (auto &powerUp : mPowerUps)
    {
        powerUp->draw(target);
    }
}

void World::drawHumanoids(sf::RenderTarget &target)
{
    for (auto &humanoid : mHumanoids)
    {
        humanoid->draw(target);
    }
}
void World::onCollission()
{
    landerCollission();
    powerUpCollission();
    asteroidCollission();
    spaceShipCollission();
    humanoidCollission();
}

void World::spaceShipCollission()
{
    // Check if Lander collides with player bullet and destroy both, player bullet and lander bullet
    for (size_t i = 0; i < mSpaceship->getBullets().size(); i++)
    {
        for (auto &lander : mLanders)
        {
            // Check if player bullet collides with lander missile
            for (size_t j = 0; j < lander->getMissiles().size(); j++)
            {
                if (mSpaceship->getBullets()[i]->getBounds().intersects(lander->getMissiles()[j]->getBounds()))
                {
                    std::cout << "World::spaceShipCollission() - Player bullet collided with lander missile" << std::endl;
                    mSpaceship->getBullets()[i]->OnDestroy(); // Destroy bullet
                    lander->getMissiles()[j]->OnDestroy(); // Destroy missile
                    mContext->mScore.updateScore(ENTITYTYPE::PROJECTILE, 5);
                    mContext->mScore.setScoreText(mContext->mFonts->getResourceById(Fonts::GamePlayed));
                    return;
                }
            }
            // Check if player bullet collides with lander
            if (mSpaceship->getBullets()[i]->getBounds().intersects(lander->getBounds()) )
            {
                std::cout << "World::spaceShipCollission() - Player bullet collided with lander -- kidnappin = " << [](bool b){return b ? "true" : "false";}(lander->isKidnapping()) << std::endl;
                if(lander->isKidnapping())
                {
                    std::cout << "World::spaceShipCollission() - drop humanoid" << std::endl;
                    lander->dropHumanoid();
                    lander->setKidnapping(false);
                }
                mSpaceship->getBullets()[i]->OnDestroy(); // Destroy bullet
                lander->OnDestroy(); // Destroy lander
                mContext->mScore.updateScore(ENTITYTYPE::ENEMY, 30);
                mContext->mScore.setScoreText(mContext->mFonts->getResourceById(Fonts::GamePlayed));
                std::cout << "World::spaceShipCollission() - Score: " << mContext->mScore.getScore() << std::endl;
                // return;
            }
        }
        // Check if player bullet collides with Humanoid
        for (auto &humanoid : mHumanoids)
        {
            if (mSpaceship->getBullets()[i]->getBounds().intersects(humanoid->getBounds()))
            {
                std::cout << "World::spaceShipCollission() - Player bullet collided with humanoid" << std::endl;
                mSpaceship->getBullets()[i]->OnDestroy(); // Destroy bullet
                humanoid->setShotDown(true);
                humanoid->OnDestroyAll(); // Destroy humanoid
                mContext->mScore.updateScore(ENTITYTYPE::HUMANOID, -20);
                mContext->mScore.setScoreText(mContext->mFonts->getResourceById(Fonts::GamePlayed));
                // return;
            }
        }
    }
}

void World::humanoidCollission()
{
    for (auto &humanoid: mHumanoids)
    {
        if(humanoid->getPosition().y >= mContext->mBottomBound && !humanoid->isRescued() && humanoid->isReleased())
        {
            // Check if humanoid collides with the ground, dropped by the lander
            std::cout << "World::humanoidCollission() - Humanoid collided with the ground" << std::endl;
            humanoid->OnDestroyAll(); // Destroy humanoid
            mContext->mScore.updateScore(ENTITYTYPE::HUMANOID, -20);
            mContext->mScore.setScoreText(mContext->mFonts->getResourceById(Fonts::GamePlayed));
        }
        else 
        {
            // check if humanoid collides with lander
            for (auto &lander : mLanders)
            {
                // && !humanoid->isReleased()
                if (humanoid->getBounds().intersects(lander->getBounds()) && !humanoid->isKidnapped() && !lander->isKidnapping())
                {
                    std::cout << "World::humanoidCollission() - Humanoid collided with lander" << std::endl; 
                    lander->setTargetHumanoid(humanoid);
                    lander->setKidnapping(true);
                    humanoid->setKidnapped(true);
                    humanoid->setRescued(false);
                    //humanoid->setReleased(false);
                }
                if (humanoid->isDead())
                {
                    // lander->initLanderState();
                }
            }
        } 

        // check if humanoid collides with player while being released
        if (humanoid->getBounds().intersects(mSpaceship->getBounds()) && !humanoid->isRescued() && humanoid->isReleased())
        {
            std::cout << "World::humanoidCollission() - Humanoid is rescued" << std::endl;
            humanoid->setRescued(true);
            humanoid->setKidnapped(false);
            mContext->mScore.updateScore(ENTITYTYPE::HUMANOID, 100);
        }
    }
}

void World::powerUpCollission()
{
    // Check if player collides with powerup
    for (auto &powerUp : mPowerUps)
    {
        if (mSpaceship->getBounds().intersects(powerUp->getBounds()))
        {
            std::cout << "World::powerUpCollission() - Player collided with powerUp" << std::endl;
            powerUp->OnDestroy(); // Destroy powerUp
            mSpaceship->setFuel(100.f);
        }
    }
}

void World::landerCollission()
{
    // Check if player collides with lander
    for (auto &lander : mLanders)
    {
        if (mSpaceship->getBounds().intersects(lander->getBounds()))
        {
            std::cout << "World::landerCollission() - Player collided with lander" << std::endl;
            mSpaceship->OnDestroy(); // Destroy player
            return;
        }

        // Check if player collides with lander missile
        for (size_t i = 0; i < lander->getMissiles().size(); i++)
        {
            if (mSpaceship->getBounds().intersects(lander->getMissiles()[i]->getBounds()))
            {
                std::cout << "World::landerCollission() - Player collided with lander missile" << std::endl;
                lander->getMissiles()[i]->OnDestroy(); // Destroy missile
                mSpaceship->OnDestroy(); // Destroy player
                return;
            }
        }
    }
}

void World::asteroidCollission()
{
    // check if player collides with asteroid
    for (auto &asteroid : mAsteroids)
    {
        if (mSpaceship->getBounds().intersects(asteroid->getBounds()))
        {
            mSpaceship->OnDestroy();
            asteroid->OnDestroy();
            return;
        }
        // Check if player bullet collides with asteroid
        for (size_t i = 0; i < mSpaceship->getBullets().size(); i++)
        {
            if (asteroid->collisionCheck(mSpaceship->getBullets()[i].get())) 
            {
                mSpaceship->getBullets()[i]->OnDestroy();
                asteroid->OnDestroy();
                mContext->mScore.updateScore(ENTITYTYPE::ASTEROID, 10);
                mContext->mScore.setScoreText(mContext->mFonts->getResourceById(Fonts::GamePlayed));
                std::cout << "World::asteroidCollission() - Asteroids destroyed: " << mContext->mScore.getScore() << std::endl;
                return;
            }
        }
    }
}

void World::updateCollisions()
{
    // Remove all destroyed landers
    for (size_t i = 0; i < mLanders.size(); i++)
    {
        // Remove all destroyed lander missiles
        for (size_t j = 0; j < mLanders[i]->getMissiles().size(); j++)
        {
            if (mLanders[i]->getMissiles()[j]->isDestroyed())
            {
                mLanders[i]->getMissiles().erase(mLanders[i]->getMissiles().begin() + j);
                std::cout << "World::updateCollisions() - Lander missile destroyed" << std::endl;
            }
        }

        if (mLanders[i]->isDestroyed())
        {
            mLanders.erase(mLanders.begin() + i);
            std::cout << "World::updateCollisions() - Lander destroyed" << std::endl;
        }
        //  remove player
    }

    // Remove all destroyed player bullets
    for (size_t i = 0; i < mSpaceship->getBullets().size(); i++)
    {
        if (mSpaceship->getBullets()[i]->isDestroyed())
        {
            mSpaceship->getBullets().erase(mSpaceship->getBullets().begin() + i);
            std::cout << "World::updateCollisions() - Player bullet destroyed" << std::endl;
        }
    } 

    // remove all destroyed asteroids
    for (size_t i = 0; i < mAsteroids.size(); i++)
    {
        if (mAsteroids[i]->isDestroyed())
        {
            mAsteroids.erase(mAsteroids.begin() + i);
        }
    }
    
    // Remove all collected powerUps
    for (size_t i = 0; i < mPowerUps.size(); i++)
    {
        if (mPowerUps[i]->isDestroyed())
        {
            mPowerUps.erase(mPowerUps.begin() + i);
            std::cout << "World::updateCollisions() - PowerUp destroyed" << std::endl;
        }
    }
    // Remove all destroyed humanoids
    for (size_t i = 0; i < mHumanoids.size(); i++)
    {
        if (mHumanoids[i]->isDestroyed())
        {
            mHumanoids.erase(mHumanoids.begin() + i); 
            std::cout << "World::updateCollisions() - Humanoid destroyed" << std::endl;
        }
        // Remove humanoid from player's abductable humanoids list, Lander's humanoids list, and from the world's humanoids list
        if(mHumanoids[i]->isDead())
        {
            mHumanoids[i]->setKidnapped(false);
            mHumanoids[i]->setRescued(false);
            mHumanoids[i]->setReleased(false);
            
            mHumanoids.erase(mHumanoids.begin() + i); // Remove humanoid from world's humanoids list
            for(auto &lander : mLanders)
            {
                lander->removeHumanoid(mHumanoids[i]); // Remove humanoid from lander's humanoids list
                std::cout << "World::updateCollisions() - Humanoid size in lander: " << lander->getHumanoidCount() << std::endl;
            }
            // Remove humanoid from player's abductable humanoids list
            mSpaceship->removeHumanoid(mHumanoids[i]);
            std::cout << "World::updateCollisions() - Humanoid size in world: " << mHumanoids.size() << std::endl;
            std::cout << "World::updateCollisions() - Humanoid size in player: " << mSpaceship->getHumanoidCount() << std::endl;
            std::cout << "World::updateCollisions() - Humanoids left: " << mHumanoids.size() << std::endl<<std::endl;
        }
    }
}

Data World::gameOver() const
{
    Data data;

    data.Lives = mSpaceship->getLives();
    data.Score = mContext->mScore.getScore();   
    data.Lose = (mSpaceship->isDestroyed() || mSpaceship->getLives() == 0);
    data.Win = (mLanders.empty());

    if(data.Lose)
    {
        std::cout << "World::gameOver() - Game over" << std::endl;
        mHighScoreManager->setHighScore(data.Score);
        mContext->mScore.reset();
        return data;
    }
    else if(data.Win)
    {
        std::cout << "World::gameOver() - Game won -- score: " << data.Score << std::endl;
        mHighScoreManager->setHighScore(data.Score);
        mContext->mScore.reset();
        return data;
    }
    return data;
}

std::shared_ptr<CommandQueue> World::getCommandQueue()
{
    return mCommandQueue;
}
