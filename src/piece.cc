#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include "piece.h"
#include "board.h"
#include "utils.h"

Piece::Piece(int board[8][8], int movementCount){
    this->movementCount = movementCount;
    setboard(board);
}

void Piece::setboard(int board[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->board[i][j] = board[i][j];
        }
    }
}

bool Piece::isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation){
    return false;
}




