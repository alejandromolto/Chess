#ifndef QUEEN_H
#define QUEEN_H

#include "board.h"
#include "piece.h"

class Queen : public Piece {
public:
    using Piece::Piece;
    bool isLegit(T_Coordinates actualLocation, T_Coordinates futureLocation) override;
    ~Queen() override = default;
};

#endif
