#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Player.hpp"
#include "LoadingState.hpp"
#include "ResourceManager.hpp"
#include "StateStack.hpp"
#include "Utills.hpp"
#include "Asteroid.hpp"
// #include "Game.hpp"
#include "Context.hpp"
#include "GameState.hpp"
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

Context context;
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
TEST_CASE("Check if a resource is successfully retrieved")
{
    TexturesHolder textures;
    textures.load(Textures::Player, "resources/textures/spaceship-1.png"); 
    CHECK(textures.resourseSize() == 1);
    CHECK_NOTHROW(textures.getResourceById(Textures::Player));

}
//Player tests
TEST_CASE("Check if player can move left")
{
    TexturesHolder textures;
    textures.load(Textures::Player, "resources/textures/spaceship-1.png"); // re
   
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Player);
    sf::Vector2f position(100.0f, 200.0f);
    
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(-50.f, 0.f);

    CHECK(animation->getSprite().getPosition() == sf::Vector2f(50.f, 200.f));

}

TEST_CASE("Check if player can move right")
{
    TexturesHolder textures;
    textures.load(Textures::Player, "resources/textures/spaceship-1.png"); // re
   
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Player);
    sf::Vector2f position(100.0f, 200.0f);
    
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(50.f, 0.f);

    CHECK(animation->getSprite().getPosition() == sf::Vector2f(150.f, 200.f));
}

TEST_CASE("Check if player can move up")
{
    TexturesHolder textures;
    textures.load(Textures::Player, "resources/textures/spaceship-1.png"); // re
   
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Player);
    sf::Vector2f position(100.0f, 200.0f);
    
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(0.f, -50.f);

    CHECK(animation->getSprite().getPosition() == sf::Vector2f(100.f, 150.f));
}
TEST_CASE("Check if player can move down")
{
    TexturesHolder textures;
    textures.load(Textures::Player, "resources/textures/spaceship-1.png"); // re
   
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Player);
    sf::Vector2f position(100.0f, 200.0f);
    
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture,sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(0.f, 50.f);

    CHECK(animation->getSprite().getPosition() == sf::Vector2f(100.f, 250.f));
}

TEST_CASE("Lander can move up")
{
    TexturesHolder textures;
    textures.load(Textures::Lander, "resources/textures/lander-1.png"); // re
   
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Lander);
    sf::Vector2f position(100.0f, 200.0f);
    
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture,sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(0.f, -50.f);

    CHECK(animation->getSprite().getPosition() == sf::Vector2f(100.f, 150.f));
}
//Lander tests
TEST_CASE("Lander can move down")
{
    TexturesHolder textures;
    textures.load(Textures::Lander, "resources/textures/lander-1.png"); // re
   
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Lander);
    sf::Vector2f position(100.0f, 200.0f);
    
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture,sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(0.f, 50.f);

    CHECK(animation->getSprite().getPosition() == sf::Vector2f(100.f, 250.f));
}

TEST_CASE("Lander can move left")
{
    TexturesHolder textures;
    textures.load(Textures::Lander, "resources/textures/lander-1.png"); // re
   
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Lander);
    sf::Vector2f position(100.0f, 200.0f);
    
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(-50.f, 0.f);

    CHECK(animation->getSprite().getPosition() == sf::Vector2f(50.f, 200.f));
}

TEST_CASE("Lander can move right")
{
    TexturesHolder textures;
    textures.load(Textures::Lander, "resources/textures/lander-1.png"); // re
   
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Lander);
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture,  sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(50.f, 0.f);

    CHECK(animation->getSprite().getPosition() == sf::Vector2f(150.f, 200.f));
}
TEST_CASE("Check if player bullets move left")
{
    //Projectile(sf::Vector2f position, sf::Vector2f direction, float movementSpeed, ProjectileType type);
    Projectile projectile(sf::Vector2f(100.f, 100.f), sf::Vector2f(1.f, 0.f), 100.f, ProjectileType::PlayerBullet);
    projectile.setMovementSpeed(100.f);
    projectile.move(-100.f, 0.f);
    CHECK(projectile.getPosition() == sf::Vector2f(0.f, 100.f));
}

TEST_CASE("Check if player bullets move right")
{
    //Projectile(sf::Vector2f position, sf::Vector2f direction, float movementSpeed, ProjectileType type);
    Projectile projectile(sf::Vector2f(100.f, 100.f), sf::Vector2f(1.f, 0.f), 100.f, ProjectileType::PlayerBullet);
    projectile.setMovementSpeed(100.f);
    projectile.move(100.f, 0.f);
    CHECK(projectile.getPosition() == sf::Vector2f(200.f, 100.f));
}

TEST_CASE("Check if lander missile can move up")
{
    Projectile projectile(sf::Vector2f(100.f, 100.f), sf::Vector2f(1.f, 0.f), 100.f, ProjectileType::Missile);
    projectile.setMovementSpeed(100.f);
    projectile.move(0.f, -100.f);
    CHECK(projectile.getPosition() == sf::Vector2f(100.f, 0.f));
}

TEST_CASE("Check if lander missile can move down")
{
    Projectile projectile(sf::Vector2f(100.f, 100.f), sf::Vector2f(1.f, 0.f), 100.f, ProjectileType::Missile);
    projectile.setMovementSpeed(100.f);
    projectile.move(0.f, 100.f);
    CHECK(projectile.getPosition() == sf::Vector2f(100.f, 200.f));
}

TEST_CASE("Check if lander missile can move left")
{
    Projectile projectile(sf::Vector2f(100.f, 100.f), sf::Vector2f(1.f, 0.f), 100.f, ProjectileType::Missile);
    projectile.setMovementSpeed(100.f);
    projectile.move(-100.f, 0.f);
    CHECK(projectile.getPosition() == sf::Vector2f(0.f, 100.f));
}

TEST_CASE("Check if lander missile can move right")
{
    Projectile projectile(sf::Vector2f(100.f, 100.f), sf::Vector2f(1.f, 0.f), 100.f, ProjectileType::Missile);
    projectile.setMovementSpeed(100.f);
    projectile.move(100.f, 0.f);
    CHECK(projectile.getPosition() == sf::Vector2f(200.f, 100.f));
}
//Asteroid tests
TEST_CASE("Check if asteroid can move down")
{
    TexturesHolder textures;
    textures.load(Textures::Lander, "resources/textures/Asteroids.png"); // re
   
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Lander);
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(0.f, 50.f);

    CHECK(animation->getSprite().getPosition() == sf::Vector2f(100.f, 250.f));
}
TEST_CASE("Check if asteroid can move left")
{
    TexturesHolder textures;
    textures.load(Textures::Lander, "resources/textures/Asteroids.png"); // re
   
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Lander);
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(-50.f, 0.f);
    CHECK(animation->getSprite().getPosition() == sf::Vector2f(50.f, 200.f));
}
TEST_CASE("Check if asteroid can move right")
{
    TexturesHolder textures;
    textures.load(Textures::Lander, "resources/textures/Asteroids.png"); // re
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Lander);
    std::unique_ptr<Animation> animation;
    animation = std::make_unique<Animation>(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    animation->setPosition(sf::Vector2f(100.f, 200.f));
    animation->getSprite().move(50.f, 0.f);
    CHECK(animation->getSprite().getPosition() == sf::Vector2f(150.f, 200.f));
}
//collision tests
TEST_CASE("Check if game entities collide with each other")
{
    TexturesHolder textures;
    textures.load(Textures::Player, "resources/textures/spaceship-1.png"); // re
    sf::Texture texture;    
    texture = textures.getResourceById(Textures::Player);
    std::unique_ptr<Animation> animation1;
    animation1 = std::make_unique<Animation>(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);
    
    std::unique_ptr<Animation> animation2;
    animation2 = std::make_unique<Animation>(&texture, sf::Vector2i(0, 6), sf::Vector2i(22, 6), 1, sf::seconds(0.2f), true);

    animation1->setPosition(sf::Vector2f(100.f, 200.f));
    animation1->getSprite().move(50.f, 0.f);

    animation2->setPosition(sf::Vector2f(150.f, 200.f));

    CHECK(animation1->getSprite().getGlobalBounds().intersects(animation2->getSprite().getGlobalBounds()));
}

//check 




