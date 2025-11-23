#include "pawn.h"

bool Pawn::isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation) {
    bool isItLegit = false;
    int dx = futurelocation.col - actualLocation.col;
    int dy = futurelocation.row - actualLocation.row;

    // WHITE PAWNS (Moving up the board)
    if (board[actualLocation.row][actualLocation.col] % 10 == 1 && movementCount % 2 == 0)
    {
        if ((dx == 0 && dy == -1 && board[futurelocation.row][futurelocation.col] % 10 == 0) ||
            (dx == 0 && dy == -2 && actualLocation.row == 6 &&
             board[futurelocation.row][futurelocation.col] % 10 == 0 &&
             board[actualLocation.row - 1][actualLocation.col] % 10 == 0) ||
            ((dx == 1 || dx == -1) && dy == -1 &&
             board[futurelocation.row][futurelocation.col] % 10 != 0 &&
             board[futurelocation.row][futurelocation.col] / 10 == 0))
        {
            isItLegit = true;
        }

        return isItLegit;
    }

    // BLACK PAWNS (Moving down the board)
    if (board[actualLocation.row][actualLocation.col] % 10 == 1 && movementCount % 2 != 0)
    {
        if ((dx == 0 && dy == 1 && board[futurelocation.row][futurelocation.col] % 10 == 0) ||
            (dx == 0 && dy == 2 && actualLocation.row == 1 &&
             board[futurelocation.row][futurelocation.col] % 10 == 0 &&
             board[actualLocation.row + 1][actualLocation.col] % 10 == 0) ||
            ((dx == 1 || dx == -1) && dy == 1 &&
             board[futurelocation.row][futurelocation.col] % 10 != 0 &&
             board[futurelocation.row][futurelocation.col] / 10 != 0))
        {
            isItLegit = true;
        }
        return isItLegit;
    }

    return isItLegit;
}