#ifndef PARALLELTASK_HPP
#define PARALLELTASK_HPP

#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Clock.hpp>
#include "Context.hpp"

class ParallelTask
{
    public:
        ParallelTask(Context &context);
        void execute();
        bool isFinished();
        float getCompletion();

    private:
        void runTask();
        void loadResources();
        void loadTextures();
        void loadFonts();
        sf::Thread mThread; // Thread running the function
        Context *mContext;
        bool mFinished;
        sf::Clock mElapsedTime;
        sf::Mutex mMutex; // Protects the clock and the completion variable
        float mCompletion;
};

#endif // PARALLELTASK_HPP