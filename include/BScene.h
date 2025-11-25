#ifndef BSCENE_H
#define BSCENE_H
#include "Scene.h"
#include "board.h"

class BScene : public Scene {
private:
public:
    using Scene::Scene;
    void setPhase(int phase){ this->phase = phase; }
protected:
    int phase = 1;
    Board board;
    T_Coordinates firstPieceCoords = {-1, -1};
    T_Coordinates secondPieceCoords = {-1, -1};
    void printBoard();
    void printBoardAndLegitMoves(T_Coordinates pieceCoords, int movementCount);
    void nextPhase(){this->phase++; }
    int getPhase(){ return phase; }
};

#endif
