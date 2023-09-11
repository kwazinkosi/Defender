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
        
        Context *mContext;
        sf::Thread mThread; // Thread running the function
        bool mFinished;
};

#endif // PARALLELTASK_HPP