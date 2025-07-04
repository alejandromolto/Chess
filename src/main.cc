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


int mainmenu(int width, int height, SDL_Renderer* renderer, SDL_Window* window);
void printBoard(Board board, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window);
void printBoardAndLegitMoves(Board board, T_Coordinates pieceCoords, int movementCount, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window);
T_Coordinates coordsTranslator(int row, char col);
T_Coordinates selectPiece(Board board, int movementCount, SDL_Renderer *renderer, SDL_Window *window);
bool nullCoord(T_Coordinates Coord);

int main(){
    
    //Variables initialization
    int width = 1152;
    int height = 648;
    bool matchOver = false;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    Board board;
    
    // CODE

    int option = mainmenu(width, height, renderer, window);
    
    
    if(option == -1){
        return 0;
    }

    // GAME LOOP:

        int movementCount = 0;
        
        while(!matchOver){

            std::vector <T_Coordinates> prohibitedSquares = board.prohibitedMoves(movementCount);
            
            if(board.isTheKingCheckMated(movementCount, prohibitedSquares)){    // LOOK FOR CHECKMATE
                if(board.isTheKingChecked(movementCount, prohibitedSquares)){
                    // CHECKMATE
                    if(movementCount % 2 == 0){ // BLACK WINS
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return 0;
                    }else{ // WHITE WINS
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return 0;
                    }

                }else{
                    // STALEMATE
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;
                }
                matchOver = true;
                // GO BACK TO THE MENU
            }

            if(board.isTheKingChecked(movementCount, prohibitedSquares)){   // LOOK FOR CHECK
                // CHECKED MESSAGE
            }

            bool validmove = false;

            while(!validmove){

                T_Coordinates actualLocation;
                T_Coordinates futureLocation;
                bool samecolor;
                printBoard(board, width, height, renderer, window);
                
                // MANAGMENT OF THE PIECE CHOOSING.
                
                
                
                    // FIRST PIECE

                    do{
                        actualLocation = selectPiece(board, movementCount, renderer, window);

                        if(nullCoord(actualLocation)){
                            return 0; // DEBUG
                        }

                    }while(!board.isPieceValid(movementCount, actualLocation));


                    do{
                        printBoardAndLegitMoves(board, actualLocation, movementCount, width, height, renderer, window); // PRINTING.
                        
                        // SECOND PIECE
                            futureLocation = selectPiece(board, movementCount, renderer, window);

                        samecolor = board.haveSameColor(actualLocation, futureLocation); 
                        


                        if(samecolor){
                            actualLocation = futureLocation;
                        }

                    }while(samecolor);
                    

                    validmove = board.isLegit(movementCount, actualLocation, futureLocation);

                    if(validmove){
                        // If the movement is legit we have to check if it leaves the king on check to see if it can be performed.
                        Board boardDuplicate(board.getboard()); // It is performed in a duplicate board
                        boardDuplicate.updateboard(actualLocation, futureLocation);
                        std::vector <T_Coordinates> prohibitedSquaresDuplicate = boardDuplicate.prohibitedMoves(movementCount);
                        if(!boardDuplicate.isTheKingChecked(movementCount, prohibitedSquaresDuplicate)){ // And it verifies that the king is not left on check
                            board.updateboard(actualLocation, futureLocation);
                        }else{
                            validmove = false;
                        }
                    }else{
                        // NOT LEGIT
                    }
                }

                if(board.isPawnPromoting(movementCount)){
                    board.PawnPromotion(movementCount, renderer);

                }

                printBoard(board, width, height, renderer, window); // PRINTING
                movementCount++;
        }


    // END

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
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

    std::vector<T_Coordinates> legitMovesVct = board.legitMoves(movementCount, pieceCoords);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            T_Coordinates tempCoord;
            tempCoord.row = i;
            tempCoord.col = j;

            if (std::find(legitMovesVct.begin(), legitMovesVct.end(), tempCoord) != legitMovesVct.end())
            {
                SDL_Rect rect;
                SDL_SetRenderDrawColor(renderer, 135, 206, 235, 20);
                rect.y = i * 600 / 8;
                rect.x = j * 600 / 8;
                rect.w = 600 / 8;
                rect.h = 600 / 8;
                SDL_RenderFillRect(renderer, &rect);
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
                }else{
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    
                    T_Coordinates nullcord;
                    nullcord.row = -1;
                    nullcord.col = -1;
                    return nullcord;
                }
            }
        }
    }

T_Coordinates nullcord;
nullcord.row = -1;
nullcord.col = -1;
return nullcord;

}

int mainmenu(int width, int height, SDL_Renderer* renderer, SDL_Window* window){
 
    importImageInRender(renderer, "assets/images/provisionalImage.jpeg", 0, 0, width, height);
    importImageInRender(renderer, "assets/images/provisionalImage.jpeg", width/3, height/8 * 4, width/3, height/8);
    SDL_RenderPresent(renderer);

    bool waiting = true;
    SDL_Event e;

    while (waiting)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                waiting = false;
                return -1;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mx = e.button.x;
                int my = e.button.y;
                if(mx >  width/3 && mx < width/3 * 2 && my > height/8 * 4 && my < height/8 * 5){
                    return 1;
                }
            }
        }
    }

return -1;

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

bool nullCoord(T_Coordinates Coord){

    if(Coord.col == -1 && Coord.row == -1){
        return true;
    }

return false;

}

/*
TODO:
Implement pawn promotion.
Fix comments in the board methods.
*/
