#include "ParallelTask.hpp"

// In the initialization list, we start the thread and set the completion to 0.
ParallelTask::ParallelTask(Context &context) 
: mThread(&ParallelTask::runTask, this)
, mContext(&context)
, mFinished(false)
, mCompletion(0.f)
{
}

/**
 * @brief This function starts the thread.
 * 
 * @details It uses a sf::Thread to run the function.
 * 
 * -The function is called from the LoadingState constructor.
 * 
 */
void ParallelTask::execute()
{
    mFinished = false;
    mThread.launch(); // Launch the thread,
}

bool ParallelTask::isFinished()
{
    sf::Lock lock(mMutex);
    return mFinished;
}

float ParallelTask::getCompletion()
{
    sf::Lock lock(mMutex);
    return mCompletion;
}

/**
 * @brief This function is the one that is run in the thread.
 * @details It is a dummy function that stalls for 10 seconds.
 * 
 * -The function is called in the constructor of the ParallelTask class.
 * 
 */
void ParallelTask::runTask()
{
    // Dummy task - stall 10 seconds.
    bool ended = false;
    static bool loaded =false;
    while (!ended)
    {
        sf::Lock lock(mMutex); // Protect the clock
        if(!loaded){
            loadResources();
            loaded =true;
        }
        
        if ((mElapsedTime.getElapsedTime().asSeconds() >= 4.f) && (loaded)) // if 5 seconds have passed and resources are loaded
        {
            ended = true;
        }
        // mCompletion is between 0 and 1
        mCompletion = mElapsedTime.getElapsedTime().asSeconds() / 4.f;
    }
    // Task ended, mark it as successful (mFinished is used in the update() function of the LoadingState class).
    {
        sf::Lock lock(mMutex);
        mFinished = true;
    }
}

void ParallelTask::loadResources()
{
    loadTextures();
    loadFonts();
    std::cout << "ParallelTask::loadResources() - Resource loading complete\n";
}

void ParallelTask::loadTextures()
{
    mContext->mBackgrounds->load(Backgrounds::MainMenuScreen, "resources/textures/background-1.jpg");
    mContext->mBackgrounds->load(Backgrounds::SplashScreen, "resources/textures/background-2.jpg");
    mContext->mBackgrounds->load(Backgrounds::Mountains, "resources/textures/mountains-10.png");
    mContext->mTextures->load(Textures::Player, "resources/textures/spaceship-2.png");
    mContext->mTextures->load(Textures::Laser, "resources/textures/laser.png");
    mContext->mTextures->load(Textures::LanderMissile, "resources/textures/02.png");
    mContext->mTextures->load(Textures::Pod, "resources/textures/pod.png");
    mContext->mTextures->load(Textures::Lander, "resources/textures/lander-3.png");
    mContext->mTextures->load(Textures::Bomber, "resources/textures/bomber-1.png");
    mContext->mTextures->load(Textures::Swarmer, "resources/textures/swammer.png");
    mContext->mTextures->load(Textures::Humanoid, "resources/textures/humanoid.png");  
    mContext->mTextures->load(Textures::Defender, "resources/textures/defender.png");
    mContext->mTextures->load(Textures::PowerUp, "resources/textures/fuel.png");
    mContext->mTextures->load(Textures::Asteroid, "resources/textures/Asteroids.png");
    
}

void ParallelTask::loadFonts()
{
    mContext->mFonts->load(Fonts::SpaceObsessed, "resources/fonts/SpaceObsessed.ttf");
    mContext->mFonts->load(Fonts::GamePlayed, "resources/fonts/GamePlayed.ttf");
    mContext->mFonts->load(Fonts::PixeloidMono, "resources/fonts/PixeloidMono.ttf");
    mContext->mFonts->load(Fonts::PixeloidSans, "resources/fonts/PixeloidSans.ttf");
    mContext->mFonts->load(Fonts::ArcadeN, "resources/fonts/ARCADE_N.ttf");
    mContext->mFonts->load(Fonts::GamePlayedOutline, "resources/fonts/GamePlayedOutline.ttf");
}
