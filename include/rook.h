#ifndef ROOK_H
#define ROOK_H

#include "board.h"
#include "piece.h"

class Rook : public Piece {
public:
    using Piece::Piece;
    bool isLegit(T_Coordinates actualLocation, T_Coordinates futureLocation) override;
    ~Rook() override = default;
};

#endif
