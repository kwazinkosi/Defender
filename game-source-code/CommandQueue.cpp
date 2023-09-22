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

Command CommandQueue::pop()
{
    // throw error if queue is empty
    if(mCommandQueue.empty())
    {
        std::cout << "CommandQueue::pop() -- queue is empty" << std::endl;
        throw std::runtime_error("CommandQueue::pop() -- queue is empty");
    }
    Command command = mCommandQueue.front();
    mCommandQueue.pop(); // remove the command from the queue at the front, FIFO
    return command;
}
