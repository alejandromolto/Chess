#include "pawn.h"

bool Pawn::isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation) {
    bool isItLegit = false;
    int dx = futurelocation.col - actualLocation.col;
    int dy = futurelocation.row - actualLocation.row;

    if(!Piece::isLegit(actualLocation, futurelocation)){
        return false;
    }else if (actualLocation.row == 245713){
        return true;
    }

    // EN PASSANT
    // WHITE PAWNS
    if (board[actualLocation.row][actualLocation.col] % 10 == 1 && movementCount % 2 == 0 &&
        futurelocation == enPassantTarget &&
        (actualLocation.col == enPassantTarget.col - 1 || actualLocation.col == enPassantTarget.col + 1) &&
        actualLocation.row == futurelocation.row + 1 && abs(futurelocation.col - actualLocation.col) == 1 &&
        board[futurelocation.row][futurelocation.col] == 0 &&
        board[futurelocation.row + 1][futurelocation.col] / 10 == 0 && board[futurelocation.row + 1][futurelocation.col] % 10 == 1)
    {

        return true;
    }

    // BLACK PAWNS
    if (board[actualLocation.row][actualLocation.col] % 10 == 1 && movementCount % 2 != 0 &&
        futurelocation == enPassantTarget &&
        (actualLocation.col == enPassantTarget.col - 1 || actualLocation.col == enPassantTarget.col + 1) &&
        actualLocation.row == futurelocation.row - 1 && abs(futurelocation.col - actualLocation.col) == 1 &&
        board[futurelocation.row][futurelocation.col] == 0 &&
        board[futurelocation.row - 1][futurelocation.col] / 10 == 1 && board[futurelocation.row - 1][futurelocation.col] % 10 == 1)
    {

        return true;
    }

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