#ifndef Utills_HPP
#define Utills_HPP

/**
 * @brief    Enum class for the actions that the player and the enemies can perform.
 * 
 */
enum class PLAYERSTATE
{
    IDLE = 1,
    MOVINGRIGHT,
    MOVINGLEFT,
    MOVINGUP,
    MOVINGDOWN,
    SHOOTING,
    DEAD,
};
/**
 * @brief  Enum class for the categories that the player and the enemies belong to.
 * 
 */
enum class ENTITYTYPE
{
    PLAYER,
    ENEMY,
    PROJECTILE,
    MINEBOMB,
    POWERUP,
    COLLIDABLE, 
    ASTEROID,
    HUMANOID,       
};
 /**
  * @brief  Enum class for the states of the enemy
  * 
  */
enum class ENEMYSTATE
{
    IDLE = 1,
    MOVINGRIGHT,
    MOVINGLEFT,
    MOVINGUP,
    MOVINGDOWN,
    SHOOTING,
    SEEK,
    DEAD,
};  
/**
 * @brief enum class categorizing the type of enemy
 * 
 */
enum class ENEMYTYPE
{
    LANDER = 1,
    BOMBER,
    POD,
    SWARMER,
    BAITER,
    MUTANT,
    HUMAN,
};

/**
 * @brief enum class for textures
 * 
 */
enum class Textures
{
    Player, Lander, Pod, Swarmer, Humanoid, Bomber, LanderMissile, Laser, Explosion, Mine,  Defender, PowerUp, Asteroid, texturesCount 
};
/**
 * @brief enum class for Backgrounds
 * 
 */
enum class Backgrounds
{
    SplashScreen,  MainMenuScreen, GameScreen, GameOverScreen, HelpScreen, OptionsScreen, ExitScreen, PauseScreen,Mountains, backgroundsCount
};
/**
 * @brief enum class for Fonts
 * 
 */
enum class Fonts
{
    arialFont, Menu, SpaceObsessed, PixeloidSans, PixeloidSansBold, PixeloidMono, ArcadeR, ArcadeN, GamePlayed, GamePlayedOutline, fontsCount
};
/**
 * @brief enum class for Sounds
 * 
 */
enum class Sounds
{
    Explosion, Laser, Missile, soundsCount
};
/**
 * @brief enum class for Music
 * 
 */
enum class Music
{
    GameMusic, musicCount
};
/**
 * @brief enum class for Animations
 * 
 */
enum class Animations
{
    EXPLOSION, animationsCount
};

#endif // Utills_HPP