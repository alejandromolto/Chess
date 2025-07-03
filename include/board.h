#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

struct T_Coordinates{ 
    int row;
    int col; 

    bool operator==(const T_Coordinates& other) const {
        return row == other.row && col == other.col;
    }
    
};

class Board{
    private:
        int board[8][8];
        bool matchOver;
    public:
        Board();
        Board(int board[8][8]);
        int (*getboard())[8] { return board; };
        void setboard(int board[8][8]);
        void printboard(int width, int height, SDL_Renderer *renderer, SDL_Window *window);   
        void updateboard(T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isThreatened(int movementCount, T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isLegit(int movementCount, T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isTheKingCheckMated(int movementCount, std::vector<T_Coordinates> prohibitedSquares);
        bool isPieceValid(int movementCount, T_Coordinates pieceCoords);
        std::vector<T_Coordinates> prohibitedMoves(int movementCount);
        std::vector<T_Coordinates> legitMoves(int movementCount, T_Coordinates actualLocation);
        bool isTheKingChecked(int movementCount, std::vector<T_Coordinates> prohibitedSquares);
        bool PawnPromotion(char language);
        bool haveSameColor(T_Coordinates actualLocation, T_Coordinates futurelocation);
};

#endif