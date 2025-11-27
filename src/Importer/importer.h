#ifndef IMPORTER_H
#define IMPORTER_H

#include <string>
#include "board.h"

class Importer {
public:
    std::vector<std::vector<int>> history;
    std::vector<std::vector<int>> gethistory(){ return history; }
    bool importGametoBoard(std::string filename, int numgame);
    int howManyGames(std::string filename);
};

#endif
