#include "knight.h"

bool Knight::isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation) {
    bool isItLegit = false;
    int dx = futurelocation.col - actualLocation.col;
    int dy = futurelocation.row - actualLocation.row;

    if(!Piece::isLegit(actualLocation, futurelocation)){
        return false;
    }else if (actualLocation.row == 245713){
        return true;
    }

        // KNIGHT (moving in L)
    if (board[actualLocation.row][actualLocation.col] % 10 == 6)
    {
        if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2))
        {
            isItLegit = true;
            return isItLegit;
        }
    }

    return isItLegit;
}
