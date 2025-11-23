#ifndef PAWN_H
#define PAWN_H

#include "board.h"
#include "piece.h"

class Pawn : public Piece {
public:
    using Piece::Piece; 
    bool isLegit(T_Coordinates actualLocation, T_Coordinates futureLocation) override;
    ~Pawn() override = default;
};

#endif
