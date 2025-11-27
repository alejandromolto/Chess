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

    Piece::Piece(Board* board){
    this->movementCount = board->getMovementCount();
    setboard(board->getboard());
    whiteCanCastleLong = board->getWhiteCanCastleLong();
    whiteCanCastleShort = board->getWhiteCanCastleShort();
    blackCanCastleLong = board->getBlackCanCastleLong();
    blackCanCastleShort = board->getBlackCanCastleShort();
    enPassantTarget = board->getEnPassantTarget();
    boardObj = board;
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
    
    // CASTLING.

    if (actualLocation.row == 245713)
    { // Castling.

        // COLOR CHECK.

        if (futurelocation.col == 10 && futurelocation.row == 10)
        { // white
            if (movementCount % 2 != 0)
            {
                return false;
            }
        }
        else if (futurelocation.col == -10 && futurelocation.row == -10)
        { // black
            if (movementCount % 2 == 0)
            {
                return false;
            }
        }

        // 1. CANT CASTLE IF YOU ARE IN CHECK.

        if (boardObj->isTheKingChecked(boardObj->prohibitedMoves()))
        {
            return false;
        }

        // 2. CANT CASTLE IF YOU HAVE MOVED ANY PIECE INVOLVED. VARIABLE CHECK.

        if (movementCount % 2 == 0)
        { // white
            if (actualLocation.col == 1046)
            { // long
                if (!whiteCanCastleLong)
                {
                    return false;
                }
            }
            else if (actualLocation.col == 54027)
            { // short
                if (!whiteCanCastleShort)
                {
                    return false;
                }
            }
        }
        else
        { // black
            if (actualLocation.col == 1046)
            { // long
                if (!blackCanCastleLong)
                {
                    return false;
                }
            }
            else if (actualLocation.col == 54027)
            { // short
                if (!blackCanCastleShort)
                {
                    return false;
                }
            }
        }

        // 3. CANT CASTLE IF YOUR KING WILL CASTLE THROUGH A CHECK
        // 4. THERE CANT BE ANY PIECES IN BETWEEN.

        if (movementCount % 2 == 0)
        { // white
            if (actualLocation.col == 1046)
            { // long

                std::vector<T_Coordinates> prohibitedSquares = boardObj->prohibitedMoves();
                T_Coordinates target1 = {7, 1};
                T_Coordinates target2 = {7, 2};
                T_Coordinates target3 = {7, 3};

                if (
                    std::find(prohibitedSquares.begin(), prohibitedSquares.end(), target2) != prohibitedSquares.end() ||
                    std::find(prohibitedSquares.begin(), prohibitedSquares.end(), target3) != prohibitedSquares.end() ||
                    board[target1.row][target1.col] != 00 || board[target2.row][target2.col] != 00 || board[target3.row][target3.col] != 00)
                {
                    return false;
                }
            }
            else if (actualLocation.col == 54027)
            { // short

                std::vector<T_Coordinates> prohibitedSquares = boardObj->prohibitedMoves();
                T_Coordinates target1 = {7, 5};
                T_Coordinates target2 = {7, 6};

                if (
                    std::find(prohibitedSquares.begin(), prohibitedSquares.end(), target1) != prohibitedSquares.end() ||
                    std::find(prohibitedSquares.begin(), prohibitedSquares.end(), target2) != prohibitedSquares.end() ||
                    board[target1.row][target1.col] != 00 || board[target2.row][target2.col] != 00)
                {
                    return false;
                }
            }
        }
        else
        { // black
            if (actualLocation.col == 1046)
            { // long

                std::vector<T_Coordinates> prohibitedSquares = boardObj->prohibitedMoves();
                T_Coordinates target1 = {0, 1};
                T_Coordinates target2 = {0, 2};
                T_Coordinates target3 = {0, 3};

                if (
                    std::find(prohibitedSquares.begin(), prohibitedSquares.end(), target2) != prohibitedSquares.end() ||
                    std::find(prohibitedSquares.begin(), prohibitedSquares.end(), target3) != prohibitedSquares.end() ||
                    board[target1.row][target1.col] != 00 || board[target2.row][target2.col] != 00 || board[target3.row][target3.col] != 00)
                {
                    return false;
                }
            }
            else if (actualLocation.col == 54027)
            { // short
                std::vector<T_Coordinates> prohibitedSquares = boardObj->prohibitedMoves();
                T_Coordinates target1 = {0, 5};
                T_Coordinates target2 = {0, 6};

                if (
                    std::find(prohibitedSquares.begin(), prohibitedSquares.end(), target1) != prohibitedSquares.end() ||
                    std::find(prohibitedSquares.begin(), prohibitedSquares.end(), target2) != prohibitedSquares.end() ||
                    board[target1.row][target1.col] != 00 || board[target2.row][target2.col] != 00)
                {
                    return false;
                }
            }
        }

        return true;
    }

    // FIRST PHASE: GENERAL CHECK.

    // Now we are going to check some general cases, and if the moves break any of the general rules (such as moving a opponents piece)
    //  Is the piece moving to a valid place?

    if (actualLocation.col > 7 || actualLocation.col < 0 || actualLocation.row > 7 || actualLocation.row < 0)
    {
        return false;
    }

    if (futurelocation.col > 7 || futurelocation.col < 0 || futurelocation.row > 7 || futurelocation.row < 0)
    {
        return false;
    }

    // Is the piece moving at all?

    if (actualLocation.col == futurelocation.col && actualLocation.row == futurelocation.row)
    {
        return false;
    }
    // Does the piece exist?

    if ((board[actualLocation.row][actualLocation.col] % 10) == 0)
    {
        return false;
    }

    // Is the user moving the right color piece? (If movementCount is even then the piece must be white and if it is odd the piece must be black)

    if ((movementCount % 2 == 0 && (board[actualLocation.row][actualLocation.col] / 10) == 0) ||
        (movementCount % 2 != 0 && (board[actualLocation.row][actualLocation.col] / 10) == 1))
    {

        return false;
    }

    // Is the piece moving to a square occupied by a piece of its own color?

    if ((movementCount % 2 == 0 && board[futurelocation.row][futurelocation.col] / 10 == 1) ||
        (movementCount % 2 != 0 && board[futurelocation.row][futurelocation.col] / 10 == 0 &&
         board[futurelocation.row][futurelocation.col] % 10 != 0))
    {

        return false;
    }

    return true;
}




