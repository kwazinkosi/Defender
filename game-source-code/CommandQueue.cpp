#include "CommandQueue.hpp"

CommandQueue::CommandQueue()
{
    std::cout << "CommandQueue::CommandQueue() -- creating command queue" << std::endl;
}

CommandQueue::~CommandQueue()
{
}

void CommandQueue::push(Command command)
{
    //std::cout << "CommandQueue::push() -- pushing command to queue" << std::endl;
    mCommandQueue.push(command);
}
