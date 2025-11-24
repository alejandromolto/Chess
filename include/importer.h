#ifndef IMPORTER_H
#define EXPORTER_H

#include <string>
#include "board.h"

class Importer {
public:
    std::vector<std::vector<int>> history;
    bool importGametoBoard(std::string filename, int numgame);
    std::vector<std::vector<int>> gethistory(){ return history; }
};

#endif
