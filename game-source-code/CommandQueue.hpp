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
    Command() :
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
        CommandQueue();
        void push(Command command);
        Command pop();
        bool isEmpty();
        int getQueueSize() const;
    private:
        std::queue<Command> mCommandQueue; // command queue, holds commands
};
#endif // COMMANDQUEUE_HPP