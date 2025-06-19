#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include "include/utils.h"
#include "include/board.h"


void mainmenu(int &option, char &language);
void settingsmenu(int &option, char &language);
void languagemenu(int &option, char &language);
void askMovement(int movementCount, char &colPos, int &rowPos, char &colMove, int &rowMove, char &language);
void printBoard(Board board, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window);
void printBoardAndLegitMoves(Board board, T_Coordinates pieceCoords, int movementCount, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window);
T_Coordinates coordsTranslator(int row, char col);
T_Coordinates selectPiece(Board board, int movementCount, SDL_Renderer *renderer, SDL_Window *window);

int main(){

    bool varwait = true;

    //Variables initialization
    int width = 1152;
    int height = 648;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    Board board;
    
    // CODE

    T_Coordinates actualLocation;
    T_Coordinates futureLocation;

        int movementCount = 0;
        char value2;
        int value1;
        printBoard(board, width, height, renderer, window);
        
        while(varwait){
            actualLocation = selectPiece(board, movementCount, renderer, window);
            printBoardAndLegitMoves(board, actualLocation, movementCount, width, height, renderer, window);
            futureLocation = selectPiece(board, movementCount, renderer, window);
            printBoard(board, width, height, renderer, window);
            
            if(board.isLegit(movementCount, actualLocation, futureLocation)){
                board.updateboard(actualLocation, futureLocation);
            }else{
                std::cout << "not legit";
            }
            movementCount++;
        }


    // END

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}

void printBoard(Board board, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window){
    // Board decoration.
    importImageInRender(renderer, "assets/images/provisionalImage.jpeg", 0, 0, windowwidth, windowheight);
    
    // Chess board.
    board.printboard(600, 600, renderer, window);

    // Strips (A-H) and (1-8) 
    importImageInRender(renderer, "assets/images/whitepawn.png", 0, 600, 600, 120);
    importImageInRender(renderer, "assets/images/whitepawn.png", 600, 0, 120, 600);

    SDL_RenderPresent(renderer);
}

void printBoardAndLegitMoves(Board board, T_Coordinates pieceCoords, int movementCount, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window){

    // Board decoration.
    importImageInRender(renderer, "assets/images/provisionalImage.jpeg", 0, 0, windowwidth, windowheight);
    
    // Chess board.
    board.printboard(600, 600, renderer, window);

    // Strips (A-H) and (1-8) 
    importImageInRender(renderer, "assets/images/whitepawn.png", 0, 600, 600, 120);
    importImageInRender(renderer, "assets/images/whitepawn.png", 600, 0, 120, 600);

    if((board.getboard()[pieceCoords.col][pieceCoords.row]/10 == 0 && (movementCount % 2 != 0)) ||
    (board.getboard()[pieceCoords.col][pieceCoords.row]/10 == 1 && (movementCount % 2 == 0))){

        std::vector <T_Coordinates> legitMovesVct = board.legitMoves(movementCount, pieceCoords);
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){

                T_Coordinates tempCoord;
                tempCoord.row = i;
                tempCoord.col = j;


                if(std::find(legitMovesVct.begin(), legitMovesVct.end(), tempCoord) != legitMovesVct.end()){
                    SDL_Rect rect;
                    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 20); 
                    rect.y = i * 600/8;
                    rect.x = j * 600/8;
                    rect.w = 600/8;
                    rect.h = 600/8;
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }



SDL_RenderPresent(renderer);
}

T_Coordinates selectPiece(Board board, int movementCount, SDL_Renderer *renderer, SDL_Window *window){

    bool waiting = true;
    SDL_Event e;

    while (waiting)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                waiting = false;
                T_Coordinates nullcord;
                nullcord.row = -1;
                nullcord.col = -1;
                return nullcord;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mx = e.button.x;
                int my = e.button.y;
                if(mx/75 >= 0 && mx/75 < 8 && my/75 >= 0 && my/75 < 8){
                    T_Coordinates returnPiece;
                    returnPiece.col = mx / 75;
                    returnPiece.row = my / 75;
                    return returnPiece;
                }
            }
        }
    }

T_Coordinates nullcord;
nullcord.row = -1;
nullcord.col = -1;
return nullcord;

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
Develop, in order:
    The askMovement
    The mainmenu
    The settingsmenu
    The languagemenu
Fix comments in the board methods.
*/
