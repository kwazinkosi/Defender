#ifndef PROJECT_SCORE_HPP
#define PROJECT_SCORE_HPP

#include <algorithm>
#include <string>   
#include <fstream>
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "TextFormater.hpp"

class Score
{
public:
    Score();
    void updateScore(ENTITYTYPE type);
    void drawScore(sf::RenderWindow& window);
    void reset();
    const unsigned int getScore() const;
    sf::Text getScoreText();
    void setScoreText(const sf::Font& font);
    std::vector<int> mHighscores;
    void appendHighscore(int score);
    void setScore(unsigned int score);
private:
    
    sf::Text mScoreText;
    void addToScore(int points);
    unsigned int _score;
    unsigned int _enemiesKilled;    
};

#endif //PROJECT_SCORE_HPP