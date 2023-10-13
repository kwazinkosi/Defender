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
        /**
         * @brief Construct a new Mountains object 
         * 
         * @param context 
         * @param isLeft 
         * @param scrollSpeed 
         * @param posY 
         */
        Mountains(Context &context, bool isLeft, float scrollSpeed, float posY);
        /**
         * @brief Destroy the Mountains object
         * 
         */
        ~Mountains();
        /**
         *  @brief  UPDATE the mountains.
        */
        void update(sf::Time deltaTime);
        /**
         * @brief  draws the mountains to the screen.
         * 
         * @param window 
         */
        void draw(sf::RenderTarget& window);
        /**
         * @brief  Initializes the mountains.
         * 
         */
        void initMountains();
        /**
         * @brief Get the Mountain Bounds object 
         * 
         * @return sf::FloatRect 
         */
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