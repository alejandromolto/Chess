#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include "include/utils.h"
#include "include/board.h"

int mainmenu(int width, int height, SDL_Renderer* renderer, SDL_Window* window);
int singleplayerloop(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height);
int twoplayerloop(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height, std::string filename);
void reviewMatchs(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height , std::string filename);
void printBoard(Board board, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window);
void printBoardAndLegitMoves(Board board, T_Coordinates pieceCoords, int movementCount, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window);
T_Coordinates coordsTranslator(int row, char col);
T_Coordinates selectPiece(Board board, bool kingClicked, int movementCount, SDL_Renderer *renderer, SDL_Window *window);
bool nullCoord(T_Coordinates Coord);
int howMuchGames(std::string filename);
int chooseMatch(SDL_Renderer* renderer, SDL_Window* window, int width, int height, std::string filename);
bool downloadConfirmation(SDL_Renderer* renderer, int width, int height);

int main(){ 
    
    //Variables initialization
    int width = 1152;
    int height = 680;
    bool matchOver = false;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    Board board;
    
    // CODE

    int option = mainmenu(width, height, renderer, window);
    
    // Options: Exit, -1. Single play: 1. Two players: 2. Review matches: 3.
    
    if(option == -1){
        return 0;
    }else if(option == 1){
        singleplayerloop(board, renderer, window, width, height);
    }else if(option == 2){
        twoplayerloop(board, renderer, window, width, height, "chessMatches.txt");
    }else if(option == 3){
        reviewMatchs(board, renderer, window, width, height, "chessMatches.txt");
    }

    SDL_Delay(500);

    // END

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

int twoplayerloop(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height, std::string filename){

// GAME LOOP:
        
        bool matchOver = false;
        
        while(!matchOver){

            std::vector <T_Coordinates> prohibitedSquares = board.prohibitedMoves();
            
            if(board.isTheKingCheckMated(prohibitedSquares)){    // LOOK FOR CHECKMATE
                if(board.isTheKingChecked(prohibitedSquares)){
                    // CHECKMATE
                    if(board.getMovementCount() % 2 == 0){ // BLACK WINS
                        if(downloadConfirmation(renderer, width, height)){
                            board.exportGametoFile(filename);
                        }
                        return -1;
                    }else{ // WHITE WINS
                        if(downloadConfirmation(renderer, width, height)){
                            board.exportGametoFile(filename);
                        }                        
                        return 1;
                    }

                }else{
                    // STALEMATE
                    if(downloadConfirmation(renderer, width, height)){
                        board.exportGametoFile(filename);
                    }
                    return 2    ;
                }
                matchOver = true;
                // GO BACK TO THE MENU
            }

            if(board.isTheKingChecked(prohibitedSquares)){   // LOOK FOR CHECK
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
                        actualLocation = selectPiece(board, false, board.getMovementCount(), renderer, window);

                        if(nullCoord(actualLocation)){
                            return 0; // DEBUG
                        }

                    }while(!board.isPieceValid(actualLocation));


                    do{
                        printBoardAndLegitMoves(board, actualLocation, board.getMovementCount(), width, height, renderer, window); // PRINTING.
                        
                        // SECOND PIECE
                            futureLocation = selectPiece(board, board.getboard()[actualLocation.row][actualLocation.col]%10==2, board.getMovementCount(), renderer, window);
                                if(futureLocation.row == 245713){ // castling
                                    if(futureLocation.col == 1046){
                                        if(board.getMovementCount()%2==0){
                                            actualLocation = futureLocation;
                                            futureLocation = {10, 10};
                                            break;
                                        }else{
                                            actualLocation = futureLocation;
                                            futureLocation = {-10, -10};
                                            break;
                                        }
                                    }else if(futureLocation.col == 54027){
                                        if(board.getMovementCount()%2==0){
                                            actualLocation = futureLocation;
                                            futureLocation = {10, 10};
                                            break;
                                        }else{
                                            actualLocation = futureLocation;
                                            futureLocation = {-10, -10};
                                            break;
                                        }
                                    }
                                }
                        samecolor = board.haveSameColor(actualLocation, futureLocation); 
                        


                        if(samecolor){
                            actualLocation = futureLocation;
                        }

                    }while(samecolor);
                    

                    validmove = board.isLegal(actualLocation, futureLocation);

                    if(validmove){
                        board.updateboard(actualLocation, futureLocation);
                    }else{
                        // NOT LEGIT
                    }
                }

                if(board.isPawnPromoting()){
                    board.PawnPromotion(renderer);

                }

                std::cout << board.evaluate() << std::endl;

                printBoard(board, width, height, renderer, window); // PRINTING
                board.setMovementCount(board.getMovementCount()+1);

        }

        return 0;

}

int singleplayerloop(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height){

 // CHOOSE BLACK/WHITE

    importImageInRender(renderer, "assets/images/blackwhite.png", (width/3), (height/3), (width/3), (height/3));
    SDL_RenderPresent(renderer);
    bool color = true;

    bool waiting = true;
    SDL_Event e;

    while (waiting)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                waiting = false;
                return 0;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mx = e.button.x;
                int my = e.button.y;
                if(mx >= width/3 && mx <= width/3 + (width/6) && my >= height/3 && my <= height/3 + (height*2/3)){
                    color = true; // player plays as white
                    waiting = false;
                    break;
                }else if(mx >= width/3 + (width/6) && mx <= width/3 * 2 && my >= height/3 && my <= height*2/3){
                    color = false; // player plays as black
                    waiting = false;
                    break;
                }
            }
        }
    }

    bool playerMoving = color; // Si el jugador escoje blancas, juega él primero.

    // GAME LOOP:
        
        bool matchOver = false;
        
        while(!matchOver){

            std::vector <T_Coordinates> prohibitedSquares = board.prohibitedMoves();
            
            if(board.isTheKingCheckMated(prohibitedSquares)){    // LOOK FOR CHECKMATE
                if(board.isTheKingChecked(prohibitedSquares)){
                    // CHECKMATE
                    if(board.getMovementCount() % 2 == 0){ // BLACK WINS
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return -1;
                    }else{ // WHITE WINS
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return 1;
                    }

                }else{
                    // STALEMATE
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 2    ;
                }
                matchOver = true;
                // GO BACK TO THE MENU
            }

            if(board.isTheKingChecked(prohibitedSquares)){   // LOOK FOR CHECK
                // CHECKED MESSAGE
            }

            bool validmove = false;
            playerMoving=!playerMoving;

            while(!validmove){

                T_Coordinates actualLocation;
                T_Coordinates futureLocation;
                bool samecolor;
                
                // PRINTING

                printBoard(board, width, height, renderer, window);

                // MOVING.

                if(playerMoving){ // REAL PLAYER MOVING (RENDER PROCESING AND CLICKING)
                    // FIRST PIECE

                    do{
                        actualLocation = selectPiece(board, false, board.getMovementCount(), renderer, window);

                        if(nullCoord(actualLocation)){
                            return 0; // DEBUG
                        }

                    }while(!board.isPieceValid(actualLocation));


                    do{
                        printBoardAndLegitMoves(board, actualLocation, board.getMovementCount(), width, height, renderer, window); // PRINTING.
                        
                        // SECOND PIECE
                            futureLocation = selectPiece(board, board.getboard()[actualLocation.row][actualLocation.col]%10==2, board.getMovementCount(), renderer, window);
                                if(futureLocation.row == 245713){ // castling
                                    if(futureLocation.col == 1046){
                                        if(board.getMovementCount()%2==0){
                                            actualLocation = futureLocation;
                                            futureLocation = {10, 10};
                                            break;
                                        }else{
                                            actualLocation = futureLocation;
                                            futureLocation = {-10, -10};
                                            break;
                                        }
                                    }else if(futureLocation.col == 54027){
                                        if(board.getMovementCount()%2==0){
                                            actualLocation = futureLocation;
                                            futureLocation = {10, 10};
                                            break;
                                        }else{
                                            actualLocation = futureLocation;
                                            futureLocation = {-10, -10};
                                            break;
                                        }
                                    }
                                }
                        samecolor = board.haveSameColor(actualLocation, futureLocation); 
                        


                        if(samecolor){
                            actualLocation = futureLocation;
                        }

                    }while(samecolor);

                    validmove = board.isLegal(actualLocation, futureLocation);

                    if(validmove){
                        board.updateboard(actualLocation, futureLocation);
                    }else{
                        // NOT LEGIT
                    }

                    if(board.isPawnPromoting()){
                        board.PawnPromotion(renderer);
                    }
                }else{ // AI MOVING (FUNCTION THAT GENERATES MOVES)
                    std::pair<T_Coordinates, T_Coordinates> bestMove = board.bestMoveWithMinimax(3, -2147483647, +2147483647);
                    board.updateboard(bestMove.first, bestMove.second);
                    if(board.isPawnPromoting()){
                        board.AIPawnPromotion();
                    }
                    validmove = true;
                }
                // PRINTING

                printBoard(board, width, height, renderer, window); 
                }
                    
                board.setMovementCount(board.getMovementCount()+1);
        }

        return 0;

}

void reviewMatchs(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height, std::string filename){


    // REVIEW BACKGROUND

    importImageInRender(renderer, "assets/images/provisionalImage.jpeg", 0, 0, width, height);

    // GET MATCH

    
    int matchpointer = chooseMatch(renderer, window, width, height, filename) - 1;

        if(matchpointer == -1 || matchpointer > howMuchGames(filename)){
        return;
    }


    // GET BOARD

    int boardpointer = 0; // This pointer points to the board that the user is reviewing.

    // IMPORT

    board.importGametoBoard(filename, matchpointer);

    std::vector <std::vector <int>> game = board.gethistory();
    std::cout << board.gethistory().size();


    importImageInRender(renderer, "assets/images/provisionalImage.jpeg", 0, 0, width, height); // Match background
    importImageInRender(renderer, "assets/images/Leftarrow.png", 600+10, 600-200, 200, 200);
    importImageInRender(renderer, "assets/images/Rightarrow.png", 600+210, 600-200, 200, 200);


        while(true){

            int gameBoard[8][8];
            int cont = 0; 
            
            for(int i = 0; i < 8; i++){ // Decompress
                for(int j = 0; j<8; j++){
                    gameBoard[i][j] = game[boardpointer][cont];
                    cont++;
                }
            }            
            
            board.setboard(gameBoard);
            board.printboard(600, 600, renderer, window);
            SDL_RenderPresent(renderer);

            bool waiting = true;
            SDL_Event e;

            while (waiting)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                    {
                        return;
                    }
                    else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                    {
                        int mx = e.button.x;
                        int my = e.button.y;

                        if (mx > 600 + 10 && mx < 600 + 10 + 200 && my > 600 - 200 && my < 600 - 200 + 200)
                        {
                            boardpointer--;
                            waiting = false;
                            break;
                        }
                        else if (mx > 600 + 210 && mx < 600 + 210 + 200 && my > 600 - 200 && my < 600 - 200 + 200)
                        {
                            boardpointer++;
                            waiting = false;
                            break;
                        }
                    }
                }
            }

            if(boardpointer < 0 || boardpointer >= game.size()){
                break;
            }

    }        

}

void printBoard(Board board, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window){
    // Board decoration.
    SDL_Rect rect;
    SDL_SetRenderDrawColor(renderer, 84, 84, 84, 255); // blanco 
    rect.x = 0;
    rect.y = 0;
    rect.w = windowwidth;
    rect.h = windowheight;
    SDL_RenderFillRect(renderer, &rect);

    // Chess board.
    board.printboard(600, 600, renderer, window);

    // Strips (A-H) and (1-8) 
    importImageInRender(renderer, "assets/images/letterBar.png", 0, 600, 600, 80);
    importImageInRender(renderer, "assets/images/numberBar.png", 600, 0, 80, 600);


    SDL_RenderPresent(renderer);
}

void printBoardAndLegitMoves(Board board, T_Coordinates pieceCoords, int movementCount, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window){

    // Board decoration.
    SDL_Rect rect;
    SDL_SetRenderDrawColor(renderer, 84, 84, 84, 255); // blanco 
    rect.x = 0;
    rect.y = 0;
    rect.w = windowwidth;
    rect.h = windowheight;
    SDL_RenderFillRect(renderer, &rect);
    
    // Chess board.
    board.printboard(600, 600, renderer, window);

    // Strips (A-H) and (1-8) 
    importImageInRender(renderer, "assets/images/letterBar.png", 0, 600, 600, 80);
    importImageInRender(renderer, "assets/images/numberBar.png", 600, 0, 80, 600);

    // Legal moves (except castling)
    std::vector<T_Coordinates> legitMovesVct = board.legitMoves(pieceCoords);
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

    // Castling
    if(board.getboard()[pieceCoords.row][pieceCoords.col]%10==2){
        if(movementCount%2==0 && pieceCoords.row==7 && pieceCoords.col==4){

            T_Coordinates tempCoord1Long = {245713, 1046};
            T_Coordinates tempCoord1Short = {245713, 54027};
            T_Coordinates tempCoord2 = {10 , 10};

            if(board.isLegit(tempCoord1Long, tempCoord2)){ // White long    
                SDL_Rect rect;
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
                rect.y = 7 * 600 / 8;
                rect.x = 2 * 600 / 8;
                rect.w = 600 / 8;
                rect.h = 600 / 8;
                SDL_RenderFillRect(renderer, &rect);      
            }          
            if(board.isLegit(tempCoord1Short, tempCoord2)){ // White short
                SDL_Rect rect;
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
                rect.y = 7 * 600 / 8;
                rect.x = 6 * 600 / 8;
                rect.w = 600 / 8;
                rect.h = 600 / 8;
                SDL_RenderFillRect(renderer, &rect);  
            }
        }else if(movementCount%2!=0 && pieceCoords.row ==0 && pieceCoords.col==4){
            T_Coordinates tempCoord1Long = {245713, 1046};
            T_Coordinates tempCoord1Short = {245713, 54027};
            T_Coordinates tempCoord2 = {-10 , -10}; 

            if(board.isLegit(tempCoord1Long, tempCoord2)){ // Black long
                SDL_Rect rect;
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
                rect.y = 0;
                rect.x = 2 * 600 / 8;
                rect.w = 600 / 8;
                rect.h = 600 / 8;
                SDL_RenderFillRect(renderer, &rect);
            }  
            if(board.isLegit(tempCoord1Short, tempCoord2)){ // Black short
                SDL_Rect rect;
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
                rect.y = 0;
                rect.x = 6 * 600 / 8;
                rect.w = 600 / 8;
                rect.h = 600 / 8;
                SDL_RenderFillRect(renderer, &rect);  
            }
        }
    }

SDL_RenderPresent(renderer);
}

T_Coordinates selectPiece(Board board, bool kingClicked, int movementCount, SDL_Renderer *renderer, SDL_Window *window){

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

                if(kingClicked){
                    T_Coordinates longCastle = {245713, 1046};
                    T_Coordinates shortCastle = {245713, 54027};
                    T_Coordinates white = {10, 10};
                    T_Coordinates black = {-10, -10};

                    if(board.isLegit(longCastle, white)){ // white long
                        if(mx/75 >= 2 && mx/75 < 3 && my/75 >= 7 && my/75 < 8){
                        return longCastle;
                        }
                    }                   
                    if(board.isLegit(longCastle, black)){ // black long
                        if(mx/75 >= 2 && mx/75 < 3 && my/75 >= 0 && my/75 < 1){
                        return longCastle;
                        }
                    }                   
                    if(board.isLegit(shortCastle, white)){ // white short
                        if(mx/75 >= 6 && mx/75 < 7 && my/75 >= 7 && my/75 < 8){
                        return shortCastle;
                        }
                    }                   
                    if(board.isLegit(shortCastle, black)){ // black short
                        if(mx/75 >= 6 && mx/75 < 7 && my/75 >= 0 && my/75 < 1){
                        return shortCastle;
                        }
                    }
                }
                
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
    importImageInRender(renderer, "assets/images/mainbackground.png", 0, 0, width, height);
    importImageInRender(renderer, "assets/images/singleplayer.png", width/3 - 20, height/8 * 3, width/6, width/6);
    importImageInRender(renderer, "assets/images/twoplayers.png", width/2 + width/24 - 20, height/8 * 3, width/6, width/6);
    importImageInRender(renderer, "assets/images/reviewgames.png", width/3 - 20, height/8 * 6, width*3/8, height/5);
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
                if (mx > width/3 - 20 && mx < width/3 - 20 + width/6 && my > height/8 * 3 && my < height/8 * 3 + width/6) {
                    return 1;
                } else if (mx > width/2 + width/24 - 20 && mx < width/2 + width/24 - 20 + width/6 && my > height/8 * 3 && my < height/8 * 3 + width/6) {
                    return 2;
                } else if (mx > width/3 - 20 && mx < width/3 - 20 + width*3/8 && my > height/8 * 6 && my < height/8 * 6 + height/5) {
                    return 3;
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

int howMuchGames(std::string filename){

    std::ifstream file(filename);

    if (!file.is_open()){
        return 0;
    }

    int count = 0;
    std::string line;

    while (std::getline(file, line)){
        if (line == "# [GAME]"){
            ++count;
        } 
    }

    return count;

}

int chooseMatch(SDL_Renderer* renderer, SDL_Window* window, int width, int height, std::string filename){

    importImageInRender(renderer, "assets/images/ChooseGameBackground.png", 0, 0, width, height);
    int ngames = howMuchGames(filename);

    for(int i = 0; i < 10; i++){
        std::string numberfile = "assets/images/";
        numberfile += std::to_string((i+1));
        numberfile += ".png";
        importImageInRender(renderer,
            numberfile,
            width/4 + (width/4)*(i%2) + 5*(i%2) + 45,
            (height/6)*(i/2) + height/6 + 5*(i/2),
            width/8,
            height/12);

        if(i < ngames){
            SDL_Rect greenSquare;
            greenSquare.x = width/4 + (width/4)*(i%2) + 5*(i%2) + 45;
            greenSquare.y = (height/6)*(i/2) + height/6 + 5*(i/2);
            greenSquare.w = width/8;
            greenSquare.h = height/12;
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
            SDL_RenderFillRect(renderer, &greenSquare);
        }
    }
    SDL_RenderPresent(renderer);

    bool waiting = true;
    SDL_Event e;

    while (waiting)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                return -1;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mx = e.button.x;
                int my = e.button.y;

                if (mx > width/4 + 45 && mx < width/4 + 45 + width/8 && my > height/6 && my < height/6 + height/12 && ngames > 0)
                    return 1;
                else if (mx > width/2 + 50 && mx < width/2 + 50 + width/8 && my > height/6 && my < height/6 + height/12 && ngames > 1)
                    return 2;
                else if (mx > width/4 + 45 && mx < width/4 + 45 + width/8 && my > height/3 + 5 && my < height/3 + 5 + height/12 && ngames > 2)
                    return 3;
                else if (mx > width/2 + 50 && mx < width/2 + 50 + width/8 && my > height/3 + 5 && my < height/3 + 5 + height/12 && ngames > 3)
                    return 4;
                else if (mx > width/4 + 45 && mx < width/4 + 45 + width/8 && my > height/2 + 10 && my < height/2 + 10 + height/12 && ngames > 4)
                    return 5;
                else if (mx > width/2 + 50 && mx < width/2 + 50 + width/8 && my > height/2 + 10 && my < height/2 + 10 + height/12 && ngames > 5)
                    return 6;
                else if (mx > width/4 + 45 && mx < width/4 + 45 + width/8 && my > height*2/3 + 15 && my < height*2/3 + 15 + height/12 && ngames > 6)
                    return 7;
                else if (mx > width/2 + 50 && mx < width/2 + 50 + width/8 && my > height*2/3 + 15 && my < height*2/3 + 15 + height/12 && ngames > 7) 
                    return 8;
                else if (mx > width/4 + 45 && mx < width/4 + 45 + width/8 && my > height*5/6 + 20 && my < height*5/6 + 20 + height/12  && ngames > 8)
                    return 9;
                else if (mx > width/2 + 50 && mx < width/2 + 50 + width/8 && my > height*5/6 + 20 && my < height*5/6 + 20 + height/12 && ngames > 1)
                    return 10;
            }
        }
    }

    return 0;
}

bool downloadConfirmation(SDL_Renderer* renderer, int width, int height){
    importImageInRender(renderer, "assets/images/downloadboard.png", width/2 - 200, height/2 - 200, 400, 400);
    importImageInRender(renderer, "assets/images/yes.png", width/2 - 200, height/2 + 50, 100, 100);
    importImageInRender(renderer, "assets/images/no.png", width/2 +  50, height/2 + 50, 100, 100);
    SDL_RenderPresent(renderer);

    bool waiting = true;
    SDL_Event e;

    while (waiting)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                return -1;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mx = e.button.x;
                int my = e.button.y;

                if (mx > width/2 - 200 && mx < width/2 - 200+100 && my > height/2 + 50 && my < height/2 + 50 + 100)
                {
                    return true; // yes.
                }
                else if (mx > width/2 + 50 && mx < width/2 + 50+100 && my > height/2 + 50 && my < height/2 + 50 + 100)
                {
                    return false; // no.
                }
            }
        }
    }

    return false;
}


/*
TODO:
    Make the AI stronger.
*/
    