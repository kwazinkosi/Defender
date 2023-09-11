#include "ParallelTask.hpp"

// In the initialization list, we start the thread and set the completion to 0.
ParallelTask::ParallelTask(Context &context) : mThread(&ParallelTask::runTask, this), mFinished(false) , mCompletion(0.f), mContext(&context)
{
}

void ParallelTask::execute()
{
}

bool ParallelTask::isFinished()
{
}

float ParallelTask::getCompletion()
{   
}

void ParallelTask::runTask()
{
}