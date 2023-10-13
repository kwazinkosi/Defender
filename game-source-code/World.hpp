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
#include "Score.hpp"
#include "HighScoreManager.hpp"
#include "Asteroid.hpp"
#include "Humanoid.hpp"

/**
 * @brief Class for world.
 *
 * @details This class creates the world, which is the background, the player, and the enemies.
 *          The world is responsible for updating the player and the enemies, and for drawing
 *          the background and the player and enemies. The background is a scrolling background,
 *          it consists of three layers, the ground,  the mountains and the sky. The mountains are the bottom layer,
 *          and the sky is the top layer. The sky consists of stars, which are generated by the
 *          StarGenerator class. The mountains are a scrolling texture, which is created by the
 *          Mountains class. The player is a defender spaceship, which is controlled by the player.
 *          The enemies are attacking spaceships, which are controlled by the computer.
 *
 *          The use of the CommandQueue class allows the world to handle input, and to update the player
 *          and the enemies. The CommandQueue class is a queue of commands, which are structs that contain
 *          an action and a category. The action is an enum class that contains the actions that the player
 *          and the enemies can perform. The category is an enum class that contains the categories that the
 *          player and the enemies belong to. The CommandQueue class is used to handle input, and to update
 *          the player and the enemies. The CommandQueue class is used to handle input by pushing commands
 *          onto the queue. The CommandQueue class is used to update the player and the enemies by iterating
 *          through the queue and executing the commands.
 *
 *          The reason for making the command queue a shared pointer is because the world needs to pass
 *          the command queue to the player, enemies and other states so that they can push commands onto the queue.
 *
 * @todo     Add scrolling View. (Done)
 *
 * @todo     Add enemies to the world. (Done)
 * 
 * @todo     Add collision detection. (Done)
 * 
 * @todo     Add collision response.
 *
 */
struct Data
{
    bool Win = false;
    bool Lose = false;
    int Score = 0;
    int Lives = 0;
}; 
/**
 * @brief Class for world.
 *  
 * @details This class creates the world, which is the background, the player, and the enemies.
 *         The world is responsible for updating the player and the enemies, and for drawing
 *        the background and the player and enemies. The background is a scrolling background,
 *        it consists of three layers, the ground,  the mountains and the sky. The mountains are the bottom layer,
 * 
 */

class World
{
    public:
        /**
         * @brief Enum class for layers.
         *  
         * 
         */
        enum class Layer
        {
            Ground,
            Mountains,
            Sky,
            LayerCount
        };
        /**
         * @brief Construct a new World object
         * 
         * @param context 
         */
        World(Context &context);
        /**
         * @brief update the world
         * 
         * @param deltaTime 
         * @return Data 
         */
        Data update(sf::Time deltaTime);
        /**
         * @brief handle input
         * 
         * @param commands 
         * @param event 
         */
        void handleInput(CommandQueue &commands, sf::Event &event);
        /**
         * @brief handle realtime input
         * 
         * @param commands 
         */
        void handleRealtimeInput(CommandQueue &commands);
        /**
         * @brief render the world
         * 
         */
        void render();
        /**
         * @brief get the command queue
         * 
         * @return std::shared_ptr<CommandQueue> 
         */
        std::shared_ptr<CommandQueue> getCommandQueue();
        /**
         * @brief add an entity to the world
         * 
         * @param entity 
         */
        void addEntity(std::unique_ptr<Entity> entity);


    private:
        void loadTextures();
        void initEnemies();
        void initHumanoids();  
        void initpowerUps();
        void initAsteroid();

        void updateEnemies(sf::Time deltaTime);
        void updateAsteroids(sf::Time deltaTime);
        void updatePowerUps(sf::Time deltaTime);
        void updateHumanoids(sf::Time deltaTime);

        void drawView(sf::View &view);
        void drawEnemies(sf::RenderTarget &target);
        void drawAsteroids(sf::RenderTarget &target);
        void drawPowerUps(sf::RenderTarget &target);
        void drawHumanoids(sf::RenderTarget &target);

        sf::Vector2f SpawnPosition();
        void onCollission(); // handle collission
        void updateCollisions();
        Data gameOver() const;
        std::shared_ptr<CommandQueue> mCommandQueue;
        std::unique_ptr<StarGenerator> mStarGenerator;
        std::unique_ptr<Player> mSpaceship;
        std::unique_ptr<Mountains> mMountains;
        std::unique_ptr<HighScoreManager> mHighScoreManager;
        
        std::vector <std::unique_ptr<Lander>> mLanders; // This is the vector that will hold all the landers that the player shoots out.
        std::vector <std::unique_ptr<Asteroid>> mAsteroids;
        std::vector<std::shared_ptr<Humanoid>> mHumanoids; // This is the vector that will hold all the humanoids that the player can collide with, unique_ptr because we want to transfer ownership of the humanoid objects to the world.
        std::vector<std::unique_ptr<PowerUp>> mPowerUps; // This is the vector that will hold all the powerUps that the player can collide with, unique_ptr because we want to transfer ownership of the powerUp objects to the world.
        //std::shared_ptr<Humanoid> mTargHumanoid; // This is the humanoid that the lander is currently targeting.
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
        float mScrollSpeed;

};
#endif // WORLD_HPP
