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
#include "Lander.hpp"
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
        void loadTextures();
        void initEnemies();
        void initpowerUps();
        std::shared_ptr<CommandQueue> mCommandQueue;
        std::unique_ptr<StarGenerator> mStarGenerator;
        std::unique_ptr<Player> mSpaceship;
        std::unique_ptr<Mountains> mMountains;
        
        std::vector <std::unique_ptr<Lander>> mLanders; // This is the vector that will hold all the landers that the player shoots out.
        std::vector<std::unique_ptr<Entity>> mEntities; // This is the vector that will hold all the entities that the player can collide with, unique_ptr because we want to transfer ownership of the entity objects to the world.
        //std::vector<std::unique_ptr<Humanoid>> mHumanoids; // This is the vector that will hold all the humanoids that the player can collide with, unique_ptr because we want to transfer ownership of the humanoid objects to the world.
        std::vector<std::unique_ptr<PowerUp>> mPowerUps; // This is the vector that will hold all the powerUps that the player can collide with, unique_ptr because we want to transfer ownership of the powerUp objects to the world.

        Context *mContext;
        sf::RenderWindow *mWindow;
        sf::View *mWorldView;
        sf::View *mMiniMapView;
        sf::FloatRect mWorldBounds;
        sf::Vector2f mPlayerSpawnPosition;
        sf::Texture mMountainTexture;
        sf::Sprite mMountainSprite;
        sf::Text mText;
        sf::RectangleShape mBackground;
        sf::Clock mWorldClock;
        //sf::RectangleShape separatorLine;
        float mScrollSpeed;

};
#endif // WORLD_HPP
