#ifndef BISHOP_H
#define BISHOP_H

#include "board.h"
#include "piece.h"

class Bishop : public Piece {
public:
    using Piece::Piece;
    bool isLegit(T_Coordinates actualLocation, T_Coordinates futureLocation) override;
    ~Bishop() override = default;
};

#endif
