#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <functional>

enum class Action
{
    Idle,
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Shoot,
    FlipShip,
    ActionCount
};
enum class Category
{
    Player,
    Enemy,
    Projectile,
    TypeCount
};
struct Command
{
    /**
     * @brief Construct a new Command object
     * 
     */
    Command() :
        /**
         * @brief  Set the default category to player.
         * 
         */
        category(Category::Player),
        action(Action::Idle)
    {
    }
    Command(Action ac, Category cat) : // Change 'category' to 'cat' to avoid naming conflict
        category(cat),                // Use 'cat' here
        action(ac)
    {
    }

    Category category;
    Action action;
};

class CommandQueue
{
    public:
    /**
     * @brief Construct a new Command Queue object
     * 
     */
        CommandQueue();
        /**
         * @brief   Pushes a command to the queue.
         * 
         * @param command 
         */
        void push(Command command);
        /**
         * @brief  Pops a command from the queue.
         * 
         * @return Command 
         */
        Command pop();
        /**
         * @brief  Checks if the queue is empty.
         * 
         * @return true 
         * @return false 
         */
        bool isEmpty();
        /**
         * @brief Get the Queue Size object
         * 
         * @return int 
         */
        int getQueueSize() const;
    private:
        std::queue<Command> mCommandQueue; // command queue, holds commands
};
#endif // COMMANDQUEUE_HPP