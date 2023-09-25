#ifndef Utills_HPP
#define Utills_HPP

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

enum class ENEMYSTATE
{
    IDLE = 1,
    MOVINGRIGHT,
    MOVINGLEFT,
    MOVINGUP,
    MOVINGDOWN,
    SHOOTING,
    DEAD,
};  

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


enum class Textures
{
    Player, Lander, Pod, Swarmer, Humanoid, Bomber, LanderMissile, Laser, Explosion, Mine,  Defender, PowerUp, Asteroid, texturesCount 
};
enum class Backgrounds
{
    SplashScreen,  MainMenuScreen, GameScreen, GameOverScreen, HelpScreen, OptionsScreen, ExitScreen, PauseScreen,Mountains, miniMapScope, miniMapBorder, backgroundsCount
};
enum class Fonts
{
    arialFont, Menu, SpaceObsessed, PixeloidSans, PixeloidSansBold, PixeloidMono, ArcadeR, ArcadeN, GamePlayed, GamePlayedOutline, fontsCount
};

enum class Sounds
{
    Explosion, Laser, Missile, soundsCount
};

enum class Music
{
    GameMusic, musicCount
};

enum class Animations
{
    EXPLOSION, animationsCount
};

#endif // Utills_HPP