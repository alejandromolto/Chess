#include "rook.h"

bool Rook::isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation) {
    bool isItLegit = false;
    int dx = futurelocation.col - actualLocation.col;
    int dy = futurelocation.row - actualLocation.row;

        // ROOK (moving straight)

    if (board[actualLocation.row][actualLocation.col] % 10 == 4)
    {

        if ((dx != 0 && dy == 0) || (dx == 0 && dy != 0))
        {

            if (dx == 1 || dx == -1 || dy == 1 || dy == -1)
            {
                isItLegit = true;
                return isItLegit;
            }

            // #1 (The rook is moving to the right)
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

                // #2 (The rook is moving to the left)
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

            // vertical movement
            // #3 (The rook is moving down)
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
                    // #4(The rook is moving up)
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
    }

    return isItLegit;
}
