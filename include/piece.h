#ifndef _PIECE_H_
#define _PIECE_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <set>

struct T_Coordinates{ 
    int row;
    int col; 

    bool operator==(const T_Coordinates& other) const {
        return row == other.row && col == other.col;
    }
    
};

class Piece{
    protected:
        int board[8][8];
        int movementCount;
    public:

        // Constructor
        Piece(int board[8][8], int movementCount);
        void setboard(int board[8][8]);

        // Main method
        virtual bool isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation);
        virtual ~Piece() = default;
        


};

#endif