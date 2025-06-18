#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

typedef struct{
    int row;
    int col; 
} T_Coordinates;

class Board{
    private:
        int board[8][8];
        bool matchOver;
    public:
        Board();
        int (*getboard())[8] { return board; };
        void setboard(int board[8][8]);
        void printboard(int width, int height, SDL_Renderer *renderer, SDL_Window *window);   
        void updateboard(T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isThreatened(int movementCount, T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isLegit(int movementCount, T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isTheKingCheckMated(int movementCount, std::vector<T_Coordinates> prohibitedSquares);
        std::vector<T_Coordinates> prohibitedMoves(int movementCount);
        bool isTheKingChecked(int movementCount, std::vector<T_Coordinates> prohibitedSquares);
        bool PawnPromotion(char language);
};

#endif