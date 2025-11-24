#ifndef EXPORTER_H
#define EXPORTER_H

#include <string>
#include "board.h"

class Exporter {
public:
    void exportGametoFile(Board board, const std::string &filename);
};

#endif
