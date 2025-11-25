#include "importer.h"
#include <fstream>
#include <sstream>

bool Importer::importGametoBoard(std::string filename, int numgame){
    // This means that the vector "history" will hold the history of a imported game.

    bool imported = false;
    std::ifstream file(filename, std::ios::in);

    if (file.is_open())
    {

        std::vector<std::vector<int>> fileHistory;
        std::vector<int> board;
        std::string line;
        int currentgame = -1;
        int numLineBoard = 0;
        bool reading = false;

        while (getline(file, line))
        {

            if (reading)
            {
                if (numLineBoard == 8)
                {
                    fileHistory.push_back(board);
                    if (line == "# [GAME]")
                    {
                        reading = false;
                        numLineBoard = 0;
                        break;
                    }
                    else
                    {
                        numLineBoard = 0;
                        board.clear();
                    }
                }
                else
                {
                    std::istringstream iss(line);
                    int piece;
                    for (int i = 0; i < 8; ++i)
                    {
                        iss >> piece;
                        board.push_back(piece);
                        imported = true;
                    }
                    numLineBoard++;
                }
            }

            if (line == "# [GAME]")
            {
                if (reading)
                {
                    break;
                }
                if (++currentgame == numgame)
                {
                    reading = true;
                }
            }
        }

        if (imported)
        {
            history = fileHistory;
            file.close();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int Importer::howManyGames(std::string filename)
{

    // Returns how many games does the file have.

    std::ifstream file(filename);

    if (!file.is_open())
    {
        return 0;
    }

    int count = 0;
    std::string line;

    while (std::getline(file, line))
    {
        if (line == "# [GAME]")
        {
            ++count;
        }
    }

    return count;
}