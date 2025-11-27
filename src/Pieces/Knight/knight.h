#ifndef KNIGHT_H
#define KNIGHT_H

#include "board.h"
#include "piece.h"

class Knight : public Piece {
public:
    using Piece::Piece;
    bool isLegit(T_Coordinates actualLocation, T_Coordinates futureLocation) override;
    ~Knight() override = default;
};

#endif