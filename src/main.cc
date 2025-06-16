#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "include/utils.h"
#include "include/board.h"

// structs and definitions

#define SIZECHESS 8

// functions definition

void mainmenu(int* option, char* language);
void settingsmenu(int* option, char* language);
void languagemenu(int* option, char* language);
void askMovement(int movementCount, char* colPos, int* rowPos, char* colMove, int* rowMove, char* movingPiece, char language);
void coordsTranslator(int row, char col, T_Coordinates* coordinates);

// main function

int main(){



    //Variables & arrays initialization
    int movementCount = 0;
    char colPos;
    int rowPos = 0;
    char colMove;
    int rowMove = 0;
    char movingPiece;
    bool matchOver = false;
    bool isItLegit = false;
    int option = 0;
    char language = 's';
    bool checked;
    bool futurecheck;
    int nsquares;
    int dnsquares;
    bool change;
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

    // main menu

        mainmenu(&option, &language);

        if(option == 3){ //exit
            return 0;
        }

    //initializations

        board.printboard(width, heigh, renderer, window); // int width, int height, SDL_Renderer *renderer, SDL_Window *window

    // game loop

        while(matchOver == false){

        do{
            change = false;

            //Looking for check/checkmate/stalemate
            nsquares = 0;
            for(int i = 0; i < 4096; i++){
                prohibitedSquares[i].row = 0;
                prohibitedSquares[i].col = 0;
            }

            board.prohibitedMoves(movementCount, prohibitedSquares, &nsquares);
            board.isTheKingChecked(movementCount, prohibitedSquares, nsquares, &checked);

            if(checked == true){
                board.isTheKingCheckMated(movementCount, prohibitedSquares, &matchOver);
                if(matchOver == true){
                    printf("%s", (language == 's') ? "\nJaque mate.\n" : "\nYour king has been checkmated.\n");
                    if(movementCount % 2 == 0){
                        printf("%s\n", (language == 's') ? "\nLas negras ganan. Fin de la partida.\n" : "Black wins. The match has been concluded.");
                    }else{
                        printf("%s\n", (language == 's') ? "\nLas blancas ganan. Fin de la partida.\n" : "White wins. The match has been concluded.");
                    }
                }else{
                    printf("%s\n", (language == 's') ? "\nTu rey está en jaque.\n" : "\nYour king is in check.\n");
                }
            }else{
                board.isTheKingCheckMated(movementCount, prohibitedSquares, &matchOver);
                if(matchOver == true){
                    printf("%s", (language == 's') ? "\nLa partida termina en tablas. Rey ahogado.\n" : "\nThe match has cocluded in a draw. Stalemate.\n");
                    
                }
            }

            printf("\n\n\n");
            
            // User input (movement)

            if(matchOver == false){
            askMovement(movementCount, &colPos, &rowPos, &colMove, &rowMove, &movingPiece, language);

                    if(movingPiece == 'F' && colPos == 'f' && rowPos == -1){
                        board.prohibitedMoves(movementCount, prohibitedSquares, &nsquares);

                        printf("\n\n\n");
                        for(int i = 0; i < nsquares; i++){
                            printf("\n %d %d", prohibitedSquares[i].row, prohibitedSquares[i].col);
                        }
                        askMovement(movementCount, &colPos, &rowPos, &colMove, &rowMove, &movingPiece, language);
                    }

            coordsTranslator(rowPos, colPos, &actualLocation);
            coordsTranslator(rowMove, colMove, &futureLocation);
            board.isLegit(movementCount, actualLocation, futureLocation, &isItLegit);

            if(isItLegit == false){
                printf("%s", (language == 's') ? "\nEl movimiento no es válido. Inténtalo de nuevo.\n" : "\nThe movement is invalid. Try again.\n");
            }

            //To check if the movement can be performed (due to the fact that you cannot leave a king in check)
            //First we perform the move in a duplicate board

            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    boardDuplicate.setboard(board.getboard());
                }
            }
            
            //Then we check if this move leaves the king on check

            futurecheck = false;

            boardDuplicate.updateboard(actualLocation, futureLocation);
            boardDuplicate.prohibitedMoves(movementCount, duplicateProhibitedSquares, &dnsquares);
            boardDuplicate.isTheKingChecked(movementCount, duplicateProhibitedSquares, dnsquares, &futurecheck);

            if(futurecheck == true){
                printf("You cant leave your king in check!");
            }

        }
        }while(isItLegit == false || futurecheck == true);
        
        if(matchOver == false){

    
        board.updateboard(actualLocation, futureLocation);
        board.printboard(width, heigh, renderer, window);
        board.PawnPromotion(&change, language);
        if(change){
            printf("\n");
            board.printboard(width, heigh, renderer, window);
        }
        movementCount++;    
        } 
        }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}

void mainmenu(int* option, char *language){
    printf("\n\n\n\n\n\n\n");

    if(*language == 'e'){
        printf("**WELCOME TO C-CHESS**\n"
               "Work done by alejandromolto.\n\n\n"
               "OPTIONS: \n\n"
               "(1) Play chess. \n"
               "(2) Settings \n"
               "(3) Exit \n\n\n");
    } else {
        printf("**BIENVENIDO A C-CHESS**\n"
               "Trabajo hecho por alejandromolto.\n\n\n"
               "OPCIONES: \n\n"
               "(1) Jugar al ajedrez. \n"
               "(2) Opciones \n"
               "(3) Salida \n\n\n");
    }

    do {
        printf(*language == 'e' ? "Choose your option: " : "Elige tu opción: ");
        scanf(" %d", option);
        if (*option > 3 || *option < 1) {
            printf(*language == 'e' ? "Please choose a valid option: " : "Por favor, elige una opción válida:");
        }
    } while (*option > 3 || *option < 1);

    if(*option == 2){
        settingsmenu(option, language);
    }
}

void settingsmenu(int* option, char* language){
    printf("\n\n\n\n\n\n\n");
    printf("%s", *language == 'e' ? "**SETTINGS MENU**\n\n(1) Change language\n(2) Exit\n" : "**MENÚ DE CONFIGURACIÓN**\n\n(1) Cambiar idioma\n(2) Salir\n");
    printf("\n");

    do {
        printf(*language == 'e' ? "Choose your option: " : "Elige tu opción: ");
        scanf(" %d", option);
        if (*option > 2 || *option < 1) {
            printf(*language == 'e' ? "Please choose a valid option: " : "Por favor, elige una opción válida:");
        }
    } while (*option > 2 || *option < 1);

    if(*option == 1){
        languagemenu(option, language);
    } else {
        mainmenu(option, language);
    }
}

void languagemenu(int* option, char* language){
    printf("\n\n\n\n\n\n\n");
    printf("%s", *language == 'e' ? "**LANGUAGE MENU**\n\n(1) Spanish\n(2) English \n(3) Exit\n" :
                                   "**MENÚ DE IDIOMA**\n\n(1) Español\n(2) Inglés \n(3) Salir");
    printf("\n\n");

    do {
        printf(*language == 'e' ? "Choose your option: " : "Elige tu opción: ");
        scanf("%d", option);
        if (*option > 3 || *option < 1) {
            printf(*language == 'e' ? "Please choose a valid option: " : "Por favor, elige una opción válida:");
        }
    } while(*option > 3 || *option < 1);

    if(*option == 1){
        *language = 's';
        printf("\nLenguaje cambiado con éxito.");
        settingsmenu(option, language);
    } else if(*option == 2){
        *language = 'e';
        printf("\nLanguage successfully changed.");
        settingsmenu(option, language);
    }
}

void askMovement(int movementCount, char* colPos, int* rowPos, char* colMove, int* rowMove, char* movingPiece, char language){
    if(movementCount % 2 == 0){
        printf("%s", (language == 's') ? "\nEs el turno de las blancas. Cuál es la pieza que quieres mover y dónde está localizada: " :
                                         "\nIt is white's turn. What is the piece you want to move and where is it located: ");
    } else {
        printf("%s", (language == 's') ? "\nEs el turno de las negras. Cuál es la pieza que quieres mover y dónde está localizada: " :
                                         "\nIt is black's turn. What is the piece you want to move and where is it located: ");
    }

    scanf(" %c %c %d", movingPiece, colPos, rowPos);
    printf("%s", (language == 's') ? "\nY dónde la quieres mover: " : "\nAnd where do you want it to move: ");
    scanf(" %c %d", colMove, rowMove);
}

void coordsTranslator(int row, char col, T_Coordinates* coordinates){
    switch(col){
        case 'a': coordinates->col = 0; break;
        case 'b': coordinates->col = 1; break;
        case 'c': coordinates->col = 2; break;
        case 'd': coordinates->col = 3; break;
        case 'e': coordinates->col = 4; break;
        case 'f': coordinates->col = 5; break;
        case 'g': coordinates->col = 6; break;
        case 'h': coordinates->col = 7; break;
    }

    coordinates->row = 8 - row;
}
