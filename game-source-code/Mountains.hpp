#ifndef MOUNTAINS_HPP
#define MOUNTAINS_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "Context.hpp"

class Mountains
{
    public:
        Mountains(Context &context, bool isLeft, float scrollSpeed, float posY);
        ~Mountains();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& window);
        void initMountains();
        sf::FloatRect getMountainBounds() const;

    private:
        void scrollMountains(sf::Time deltaTime);
        sf::View *mWorldView; 
        sf::Sprite mMountainSprite;
        sf::Texture mMountainTexture;
        sf::FloatRect mMountainBounds;
        std::vector<sf::Sprite> mMountains;
        float mScrollSpeed;
        bool mIsLeftScrolling;
        float mPosY;
        float viewLeft;
        float viewRight;
};
#endif // #MOUNTAINS_HPP