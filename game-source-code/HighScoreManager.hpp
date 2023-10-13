#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Context.hpp"

using std::string;
using std::ios;
using std::fstream;

class HighScoreManager
{
    public:
        /**
         * @brief Construct a new High Score Manager object
         * 
         */
        HighScoreManager();
        /**
         * @brief Get the High Score object
         * 
         * @return int 
         */
        int getHighScore();
        /**
         * @brief Set the High Score object
         * 
         * @param score 
         */
        void setHighScore(int score);
        /**
         * @brief Destroy the High Score Manager object
         * 
         */
        ~HighScoreManager();

    private:
        void initScoreVector();
        int highScore_;	
        std::vector<int> highScores;	
        fstream file_; 		
        string filePath_;	
};
#endif // HIGHSCOREMANAGER_H