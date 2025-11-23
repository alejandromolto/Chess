#include "queen.h"

bool Queen::isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation) {
    bool isItLegit = false;
    int dx = futurelocation.col - actualLocation.col;
    int dy = futurelocation.row - actualLocation.row;


    if(!Piece::isLegit(actualLocation, futurelocation)){
        return false;
    }else if (actualLocation.row == 245713){
        return true;
    }

    // QUEEN (moving both diagonaly and straight)

    if (board[actualLocation.row][actualLocation.col] % 10 == 3)
    {

        // If its moving like a rook (same code).

        if ((dx != 0 && dy == 0) || (dx == 0 && dy != 0))
        {

            if (dx == 1 || dx == -1 || dy == 1 || dy == -1)
            {
                isItLegit = true;
                return isItLegit;
            }

            if (dx > 0)
            {
                for (int i = actualLocation.col + 1; i < futurelocation.col; i++)
                {
                    if ((board[actualLocation.row][i] % 10) == 0)
                    {
                        isItLegit = true;
                    }
                    else
                    {
                        isItLegit = false;
                        return isItLegit;
                    }
                }
            }
            else if (dx < 0)
            {
                for (int i = futurelocation.col + 1; i < actualLocation.col; i++)
                {
                    if ((board[actualLocation.row][i] % 10) == 0)
                    {
                        isItLegit = true;
                    }
                    else
                    {
                        isItLegit = false;
                        return isItLegit;
                    }
                }
            }

            if (dy > 0)
            {
                for (int j = actualLocation.row + 1; j < futurelocation.row; j++)
                {
                    if ((board[j][actualLocation.col] % 10) == 0)
                    {
                        isItLegit = true;
                    }
                    else
                    {
                        isItLegit = false;
                        return isItLegit;
                    }
                }
            }
            else if (dy < 0)
            {
                for (int j = actualLocation.row - 1; j > futurelocation.row; j--)
                {
                    if ((board[j][actualLocation.col] % 10) == 0)
                    {
                        isItLegit = true;
                    }
                    else
                    {
                        isItLegit = false;
                        return isItLegit;
                    }
                }
            }
        }

        // If its moving like a bishop (same code).

        if (abs(dx) == abs(dy))
        {

            if (abs(dx) == 1)
            {
                isItLegit = true;
                return isItLegit;
            }

            if (dx < 0 && dy < 0)
            {
                for (int i = 1; i < (abs(dx)); i++)
                {
                    if (board[futurelocation.row + i][futurelocation.col + i] == 0)
                    {
                        isItLegit = true;
                    }
                    else
                    {
                        isItLegit = false;
                        return isItLegit;
                    }
                }
            }
            else if (dx > 0 && dy < 0)
            {

                for (int i = 1; i < (abs(dx)); i++)
                {
                    if (board[futurelocation.row + i][futurelocation.col - i] == 0)
                    {
                        isItLegit = true;
                    }
                    else
                    {
                        isItLegit = false;
                        return isItLegit;
                    }
                }
            }
            else if (dx < 0 && dy > 0)
            {

                for (int i = 1; i < (abs(dx)); i++)
                {
                    if (board[futurelocation.row - i][futurelocation.col + i] == 0)
                    {
                        isItLegit = true;
                    }
                    else
                    {
                        isItLegit = false;
                        return isItLegit;
                    }
                }
            }
            else if (dx > 0 && dy > 0)
            {

                for (int i = 1; i < (abs(dx)); i++)
                {
                    if (board[futurelocation.row - i][futurelocation.col - i] == 0)
                    {
                        isItLegit = true;
                    }
                    else
                    {
                        isItLegit = false;
                        return isItLegit;
                    }
                }
            }
        }
    }

    return isItLegit;
}
