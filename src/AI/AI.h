#ifndef AI_H
#define AI_H

#include "board.h"
#include <utility>

class AI {
private:
    Board* board; 
    int searchDepth;
    int maxi(int depth, int alpha, int beta );
    int mini(int depth, int alpha, int beta);
    int evaluate();
public:
    AI(const Board* board, int searchDepth);
    void AIPawnPromotion();
    std::pair<T_Coordinates, T_Coordinates> bestMoveWithMinimax(int alpha, int beta);
};

#endif