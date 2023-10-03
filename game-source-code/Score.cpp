#include "Score.hpp"

Score::Score()
{
    mHighscores.reserve(10);
    _score = 0.f;
    _enemiesKilled = 0.f;
}

void Score::updateScore(ENTITYTYPE type)
{
    _enemiesKilled++;

    switch (type)
    {
        case ENTITYTYPE::ASTEROID:
            addToScore(20);
            break;
        case ENTITYTYPE::ENEMY:
            addToScore(30);
            
        default:
            break;
    }   
}

void Score::setScoreText(const sf::Font& font)
{
    mScoreText.setFont(font);
    mScoreText.setString("Score: " + std::to_string(_score));
    mScoreText.setCharacterSize(20);
    mScoreText.setFillColor(sf::Color::White);
    mScoreText.setPosition(10, 30.f);
}

void Score::drawScore(sf::RenderWindow& window)
{
    window.draw(mScoreText);
}

sf::Text Score::getScoreText()
{
    return mScoreText;   
}
void Score::appendHighscore(int score)
{
      
}

void Score::setScore(unsigned int score)
{
    _score = score;
}

void Score::reset()
{
    _score = 0;
    _enemiesKilled = 0;
}

const unsigned int Score::getScore() const
{
    return _score;
}

void Score::addToScore(int points)
{
    _score += points;
}
