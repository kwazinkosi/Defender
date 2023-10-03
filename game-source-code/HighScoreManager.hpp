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

        HighScoreManager();
        int getHighScore();
        void setHighScore(int score);
        ~HighScoreManager();

    private:
        void initScoreVector();
        int highScore_;	
        std::vector<int> highScores;	
        fstream file_; 		
        string filePath_;	
};
#endif // HIGHSCOREMANAGER_H