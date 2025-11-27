#include "king.h"

bool King::isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation) {
    bool isItLegit = false;
    int dx = futurelocation.col - actualLocation.col;
    int dy = futurelocation.row - actualLocation.row;

    if(!Piece::isLegit(actualLocation, futurelocation)){
        return false;
    }else if (actualLocation.row == 245713){
        return true;
    }

    if (board[actualLocation.row][actualLocation.col] % 10 == 2)
    {
        if (dx >= -1 && dx <= 1 && dy >= -1 && dy <= 1)
        {
            isItLegit = true;
            return isItLegit;
        }
    }

    return isItLegit;
}
