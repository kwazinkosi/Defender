#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include "StarGenerator.hpp"
#include "Player.hpp"
#include "Mountains.hpp"
#include "CommandQueue.hpp"
#include "Context.hpp"
#include "Entity.hpp"
#include "PowerUp.hpp"

class World
{
    public:
        World(Context &context);
        std::pair<bool, int> update(sf::Time deltaTime);
        void handleInput(CommandQueue &commands, sf::Event &event);
        void handleRealtimeInput(CommandQueue &commands);
        void render();
        std::shared_ptr<CommandQueue> getCommandQueue();
        void addEntity(std::unique_ptr<Entity> entity);


    private:
        std::shared_ptr<CommandQueue> mCommandQueue;
        std::unique_ptr<StarGenerator> mStarGenerator;
        std::unique_ptr<Player> mSpaceship;
        std::unique_ptr<Mountains> mMountains;

};
#endif // WORLD_HPP
