#ifndef Context_HPP
#define Context_HPP

#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>

typedef ResourceManager<sf::Texture, Textures> TexturesHolder; // Typedef for the Textures resource manager.
typedef ResourceManager<sf::Texture, Backgrounds> BackgroundsHolder; // Typedef for the Backgrounds resource manager.
typedef ResourceManager<sf::Font, Fonts> FontsHolder; // Typedef for the Fonts resource manager.

class ContextInitializationException{};
class Context
{
    public:
        Context();
        ~Context();
        std::unique_ptr<BackgroundsHolder> mBackgrounds; // Unique pointer to the Backgrounds resource manager. 
        std::unique_ptr<TexturesHolder> mTextures; // Unique pointer to the Textures resource manager.
        std::unique_ptr<FontsHolder> mFonts;
        sf::RenderWindow mWindow;
};
#endif // Context_HPP