#include "bishop.h"

bool Bishop::isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation)
{
    bool isItLegit = false;
    int dx = futurelocation.col - actualLocation.col;
    int dy = futurelocation.row - actualLocation.row;

    // BISHOP (moving diagonally)

   
    if (board[actualLocation.row][actualLocation.col] % 10 == 5)
    {

        if (abs(dx) == abs(dy))
        {

            if (abs(dx) == 1)
            {
                isItLegit = true;
                return isItLegit;
            }

            // #1: moving to the second quadrant
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
                // #2: moving to the first quadrant
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
                // #3: moving to the third quadrant
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
                // #4: moving to the fourth quadrant
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
        else
        {
            isItLegit = false;
            return isItLegit;
        }
    }

    return isItLegit;
}
