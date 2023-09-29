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
    

}
//Testing StateStack functionality

TEST_CASE("StateStack is empty upon creation") {
    StateStack stack;
    
    CHECK(stack.isEmpty());
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
TEST_CASE("Check if a resource is successfully loaded")
{
    //std::unique_ptr<TexturesHolder> mTextures; 
    TexturesHolder textures;
    textures.load(Textures::Player, "resources/textures/spaceship-1.png");
    //textures.load(textures::BulletPlayer, "resources/bullet_player.png");
    //CHECK_NOTHROW(textures.load(Textures::Player, "resources/textures/spaceship-1.png"));
    CHECK(textures.resourseSize() == 1);

}

TEST_CASE("Check if a font is successfully loaded")
{
    //std::unique_ptr<TexturesHolder> mTextures; 
    FontsHolder fonts;
    fonts.load(Fonts::SpaceObsessed, "resources/fonts/SpaceObsessed.ttf");
    //textures.load(textures::BulletPlayer, "resources/bullet_player.png");
    //CHECK_NOTHROW(textures.load(Textures::Player, "resources/textures/spaceship-1.png"));
    CHECK(fonts.resourseSize() == 1);

}