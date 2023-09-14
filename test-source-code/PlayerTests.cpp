#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Player.hpp"
#include "LoadingState.hpp"
#include "ResourceManager.hpp"
#include "StateStack.hpp"
#include "Utills.hpp"
// #include "Game.hpp"
#include "Context.hpp"
#include "GameState.hpp"
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

Context context;
Player player{context};
// Screen bounds

auto windowRight = context.mWindow.getSize().x;
auto windowDown = context.mWindow.getSize().y;

// player bounds
auto playerLeft = player.getBoundingBox().left;
auto playerWidth = player.getBoundingBox().width;
auto playerHeight = player.getBoundingBox().height;
auto playerTop = player.getBoundingBox().top;

TEST_CASE("Context initialization") {
    CHECK_NOTHROW(Context context);
    
    
    CHECK(context.mWindow.isOpen());
    CHECK(context.mBackgrounds != nullptr);
    CHECK(context.mFonts != nullptr);
    CHECK(context.mTextures != nullptr);
}
//Testing LoadingState
TEST_CASE("ResourceManager - getResourceById") {
    ResourceManager<sf::Texture, Textures> textureManager; // Create a texture manager
    
    // Add textures to the manager
    textureManager.load(Textures::Player, "resources/textures/spaceship.png");
    
    // Test getting an existing texture
    CHECK_NOTHROW(textureManager.getResourceById(Textures::Player));
    
    // Test getting a non-existing texture
    //CHECK_THROWS_AS(textureManager.getResourceById(Textures::NonExistent), std::runtime_error);
}
//Testing StateStack functionality

TEST_CASE("StateStack is empty upon creation") {
    StateStack stack;
    
    CHECK(stack.isEmpty());
}

TEST_CASE("Poping an empty stack throws an exception") {
    StateStack stack;
   
    // Attempt to pop an empty stack (expecting an exception)
    CHECK_THROWS_AS(stack.popState(), StateStackException);
}

TEST_CASE("StateStack - Clear States") {
    StateStack stack;
    Context context;
    
    // Push multiple states
    stack.pushState(States::MainMenuState);
    stack.pushState(States::GameState);
    stack.pushState(States::PauseState);
    
    // Clear all states and check if the stack is empty
    stack.clearStates();
    CHECK(stack.isEmpty());
}

TEST_CASE("Player initialization and getters")
{

    // CHECK(player.mPlayer.getRadius().== 30.f); // Radius * 2
    // CHECK(player.getBoundingBox().height == 30.f);
    CHECK(player.getPosition() == sf::Vector2f(100.f, 100.f));
    CHECK(player.getCollisionType() == "Player");
    CHECK(player.getCollisionResponse() == "Player");
    CHECK(player.isStatic() == false);
}
TEST_CASE("Player moves up")
{

    sf::Time deltaTime = sf::seconds(1.f); // 1 second
    player.setPosition(100.f, 100.f);

    player.setPlayerState(PLAYERSTATE::MOVINGUP);
    player.update(deltaTime);
    CHECK_FALSE(player.getPosition().y == 100.f);
    CHECK(player.getPosition().x == 100.f);
    CHECK(player.getPosition().y < 100.f);
}

TEST_CASE("Player moves down")
{

    sf::Time deltaTime = sf::seconds(1.f); // 1 second
    player.setPosition(100.f, 100.f);
    player.setPlayerState(PLAYERSTATE::MOVINGDOWN);
    player.update(deltaTime); //move up by 100 pixels, playerspeed=100.f
    CHECK_FALSE(player.getPosition().y == 100.f);
    CHECK(player.getPosition().x == 100.f);
    CHECK(player.getPosition().y > 100.f);
}

TEST_CASE("Player moves left")
{

    sf::Time deltaTime = sf::seconds(1.f); // 1 second
    player.setPosition(100.f, 100.f);
    player.setPlayerState(PLAYERSTATE::MOVINGLEFT);
    player.update(deltaTime);
    CHECK(player.getPosition().y == 100.f);
    CHECK_FALSE(player.getPosition().x == 100.f);
    CHECK(player.getPosition().x < 100.f);
}