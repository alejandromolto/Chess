#ifndef KING_H
#define KING_H

#include "board.h"
#include "piece.h"

class King : public Piece {
public:
    using Piece::Piece;
    bool isLegit(T_Coordinates actualLocation, T_Coordinates futureLocation) override;
    ~King() override = default;
};

#endif