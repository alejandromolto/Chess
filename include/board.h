#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
        void isThreatened(int movementCount, T_Coordinates actualLocation, T_Coordinates futurelocation, bool &isItThreatened);
        void isLegit(int movementCount, T_Coordinates actualLocation, T_Coordinates futurelocation, bool &isItLegit);
        void prohibitedMoves( int movementCount, T_Coordinates prohibitedSquares[4096], int &nsquares);
        void isTheKingChecked(int movementCount, T_Coordinates prohibitedSquares[4096], int nsquares, bool &checked);
        void isTheKingCheckMated(int movementCount, T_Coordinates prohibitedSquares[4096], bool &matchOver);
        void PawnPromotion(bool &change, char language);
};

#endif