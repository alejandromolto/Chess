#ifndef EXPORTER_H
#define EXPORTER_H

#include <string>
#include <fstream>
#include "board.h"

class Exporter {
public:
    bool exportGametoFile(Board board, const std::string &filename);
    void emptyFile(std::string filename);
 
};

#endif
