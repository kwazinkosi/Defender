#ifndef PROJECT_SCORE_HPP
#define PROJECT_SCORE_HPP

#include <algorithm>
#include <string>   
#include <fstream>
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "TextFormater.hpp"

/**
 * @brief  The score class is responsible for keeping track of the score.
 * 
 */
class Score
{
public:
    /**
     * @brief Construct a new Score object
     * 
     */
    Score();
    /**
     * @brief  updates the score.
     * 
     * @param type 
     */
    void updateScore(ENTITYTYPE type);
    /**
     * @brief  Draws the score.
     * 
     * @param window 
     */
    void drawScore(sf::RenderWindow& window);
    /**
     * @brief  Resets the score.
     * 
     */
    void reset();
    /**
     * @brief Get the Score object 
     * 
     * @return const unsigned int 
     */
    const unsigned int getScore() const;
    /**
     * @brief Get the Score Text object
     * 
     * @return sf::Text 
     */
    sf::Text getScoreText();
    /**
     * @brief Set the Score Text object
     * 
     * @param font 
     */
    void setScoreText(const sf::Font& font);
    /**
     * @brief  Saves the highscore to a file.
     * 
     */
    std::vector<int> mHighscores;
    /**
     * @brief  appending high scores
     * 
     * @param score 
     */
    void appendHighscore(int score);
    /**
     * @brief  sets the score
     * @param score
     * 
    */
    void setScore(unsigned int score);
private:
    
    sf::Text mScoreText;
    void addToScore(int points);
    unsigned int _score;
    unsigned int _enemiesKilled;    
};

#endif //PROJECT_SCORE_HPP