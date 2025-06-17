#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "include/utils.h"
#include "include/board.h"


void mainmenu(int &option, char &language);
void settingsmenu(int &option, char &language);
void languagemenu(int &option, char &language);
void askMovement(int movementCount, char &colPos, int &rowPos, char &colMove, int &rowMove, char &language);
T_Coordinates coordsTranslator(int row, char col);


int main(){

    //Variables & arrays initialization
    int width = 720;
    int heigh = 720;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(width, heigh, 0, &window, &renderer);

    T_Coordinates actualLocation;
    T_Coordinates futureLocation;

    T_Coordinates prohibitedSquares[4096];
    T_Coordinates duplicateProhibitedSquares[4096];


    Board board;
    Board boardDuplicate;

    // CODE


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}

void mainmenu(SDL_Renderer *renderer, SDL_Window *window, int &option, char &language){
 
}

void settingsmenu(SDL_Renderer *renderer, SDL_Window *window, int &option, char &language){

}

void languagemenu(SDL_Renderer *renderer, SDL_Window *window, int &option, char &language){

}

void askMovement(SDL_Renderer *renderer, SDL_Window *window, int movementCount, char &colPos, int &rowPos, char &colMove, int &rowMove, char &language){

}

T_Coordinates coordsTranslator(int row, char col){
    
    T_Coordinates coordinates;

    switch(col){
        case 'a': coordinates.col = 0; break;
        case 'b': coordinates.col = 1; break;
        case 'c': coordinates.col = 2; break;
        case 'd': coordinates.col = 3; break;
        case 'e': coordinates.col = 4; break;
        case 'f': coordinates.col = 5; break;
        case 'g': coordinates.col = 6; break;
        case 'h': coordinates.col = 7; break;
    }

    coordinates.row = 8 - row;

    return coordinates;
}

/*
TODO:
Turn prohibitedSquares into a std vector.
Develop, in order:
    The askMovement
    The mainmenu
    The settingsmenu
    The languagemenu
Fix comments in the board methods.
*/
