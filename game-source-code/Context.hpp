#ifndef Context_HPP
#define Context_HPP

#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include "Score.hpp"

typedef ResourceManager<sf::Texture, Textures> TexturesHolder; // Typedef for the Textures resource manager.
typedef ResourceManager<sf::Texture, Backgrounds> BackgroundsHolder; // Typedef for the Backgrounds resource manager.
typedef ResourceManager<sf::Font, Fonts> FontsHolder; // Typedef for the Fonts resource manager.

class ContextInitializationException{};
class Context
{
    public:
        /**
         * @brief Construct a new Context object
         * 
         */
        Context();
        /**
         * @brief Destroy the Context object
         * 
         */
        ~Context();
        std::unique_ptr<BackgroundsHolder> mBackgrounds; // Unique pointer to the Backgrounds resource manager. 
        std::unique_ptr<TexturesHolder> mTextures; // Unique pointer to the Textures resource manager.
        std::unique_ptr<FontsHolder> mFonts;
        sf::RenderWindow mWindow;

        sf::View mWorldView;
        sf::View mMiniMapView;
        sf::View mHudView; // View for the HUD(Heads Up Display)
        //std::vector<
        
        sf::RectangleShape mMapRect; // Rectangle for the minimap
        sf::RectangleShape mHudRect; // Rectangle for the HUD
        sf::RectangleShape mWorldRect; // Rectangle for the world
        Score mScore; // Score object
        float mLeftBound;
        float mRightBound;
        float mTopBound;
        float mBottomBound;
};
#endif // Context_HPP
