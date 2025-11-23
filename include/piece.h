#ifndef _PIECE_H_
#define _PIECE_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <set>

class Board;

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
        bool whiteCanCastleLong = true;
        bool whiteCanCastleShort = true;
        bool blackCanCastleLong = true;
        bool blackCanCastleShort = true;
        T_Coordinates enPassantTarget;        
        Board* boardObj;
    public:

        // Constructor
        Piece(Board* boardObj);
        void setboard(int board[8][8]);

        // Main method
        virtual bool isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation);
        virtual ~Piece() = default;
        


};

#endif