#include "HighScoreManager.hpp"

HighScoreManager::HighScoreManager()
    : filePath_{"highscore.txt"}
{
    // ctor
}

int HighScoreManager::getHighScore()
{
    file_.open(filePath_, ios::in);
    file_ >> highScore_;
    file_.close();
    return highScore_;
}

void HighScoreManager::setHighScore(int score)
{
    initScoreVector();
    highScores.push_back(score); // Add the new score to the vector
    
    std::sort(highScores.begin(), highScores.end()); // Sort the vector in ascending order
    if (highScores.size() > 10) {
            highScores.erase(highScores.begin()); // Remove the lowest score if the vector size is greater than 10
        }
    // Reopen the file in write mode, which will truncate the existing content
    file_.open(filePath_, ios::out);

    if (file_.is_open()) {
        for (int i = highScores.size() - 1; i >= 0; i--) {
            file_ << highScores[i] << std::endl; // Write the high scores to the file in descending order
        }
        file_.close();
    } else {
        std::cerr << "Error: Unable to open the file for writing high scores." << std::endl;
    }
}


HighScoreManager::~HighScoreManager()
{
    // dtor
}

void HighScoreManager::initScoreVector()
{
    file_.open(filePath_, ios::in);
    highScores.clear(); // Clear the existing content of the vector
    int score;
    // Read scores from the file and append them to the vector
    while (file_ >> score) {
        highScores.push_back(score);
    }
    file_.close();
    // Sort the vector in descending order
    std::sort(highScores.rbegin(), highScores.rend());
    std::cout << "Highscore size: " << highScores.size() << std::endl;

    // Resize the vector to a maximum of 10 scores
    highScores.resize(std::min(highScores.size(), static_cast<size_t>(10)));
}
