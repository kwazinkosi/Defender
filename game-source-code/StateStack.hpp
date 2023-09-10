#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <map>
#include <functional>
#include <cassert>
#include "State.hpp"
#include "ResourceManager.hpp"

enum class Action
{
    Push,
    Pop,
    Clear,
};
class StateStackException{};

class StateStack 
{

}

#endif // STATESTACK_HPP