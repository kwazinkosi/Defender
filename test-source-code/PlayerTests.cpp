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