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
    /**
     * @brief Construct a new Parallel Task object 
     * 
     * @param context 
     */
        ParallelTask(Context &context);
        /**
         * @brief  EXECUTE the task.
         * 
         */
        void execute();
        /**
         * @brief  Checks if the task is finished.
         * 
         * @return true 
         * @return false 
         */
        bool isFinished();
        /**
         * @brief Get the Completion object 
         * 
         * @return float 
         */
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