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

// Main screen.
int mainmenu(int width, int height, SDL_Renderer* renderer, SDL_Window* window);

// InGame related functions.
int singleplayerloop(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height, std::string filename);
int twoplayerloop(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height, std::string filename);
T_Coordinates selectPiece(Board board, bool kingClicked, int movementCount, int width, int height, SDL_Renderer *renderer, SDL_Window *window);
void PawnPromotion(Board& board, SDL_Renderer* renderer);
bool downloadConfirmation(SDL_Renderer* renderer, int width, int height);
void printBoard(Board board, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window);
void printBoardAndLegitMoves(Board board, T_Coordinates pieceCoords, int movementCount, int windowwidth, int windowheight, SDL_Renderer *renderer, SDL_Window *window);
bool isNullCoord(T_Coordinates Coord); // Complementary

// Review related functions.
int chooseMatch(SDL_Renderer* renderer, SDL_Window* window, int width, int height, std::string filename);
void reviewMatchs(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height , std::string filename);
int howManyGames(std::string filename); // Complementary
void emptyFile(std::string filename);

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
        singleplayerloop(board, renderer, window, width, height, "chessMatches.txt");
    }else if(option == 2){
        twoplayerloop(board, renderer, window, width, height, "chessMatches.txt");
    }else if(option == 3){
        reviewMatchs(board, renderer, window, width, height, "chessMatches.txt");
    }

    // END

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

int mainmenu(int width, int height, SDL_Renderer* renderer, SDL_Window* window){

    // Returns the option chosen by the user.

    importImageInRender(renderer, "assets/images/mainbackground.png", 0, 0, width, height);
    importImageInRender(renderer, "assets/images/singleplayer.png", width/3 - 20, height/8 * 3, width/6, width/6);
    importImageInRender(renderer, "assets/images/twoplayers.png", width/2 + width/24 - 20, height/8 * 3, width/6, width/6);
    importImageInRender(renderer, "assets/images/reviewgames.png", width/3 - 20, height/8 * 6, width*3/8, height/5);
    SDL_RenderPresent(renderer);

    SDL_Point click = userInput();
    if (click.x == -1) return -1;
    int mx = click.x;
    int my = click.y;
    if (mx > width/3 - 20 && mx < width/3 - 20 + width/6 && my > height/8 * 3 && my < height/8 * 3 + width/6) {
    return 1;
    } else if (mx > width/2 + width/24 - 20 && mx < width/2 + width/24 - 20 + width/6 && my > height/8 * 3 && my < height/8 * 3 + width/6) {
    return 2;
    } else if (mx > width/3 - 20 && mx < width/3 - 20 + width*3/8 && my > height/8 * 6 && my < height/8 * 6 + height/5) {
    return 3;
    }


    return -1;
}

int twoplayerloop(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height, std::string filename){

    // Returns 1 (White win), -1 (Black win), 2 (Stalemate)
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
                        actualLocation = selectPiece(board, false, board.getMovementCount(), width, height ,renderer, window);

                        if(isNullCoord(actualLocation)){
                            return 0; // DEBUG
                        }

                    }while(!board.isPieceValid(actualLocation));


                    do{
                        printBoardAndLegitMoves(board, actualLocation, board.getMovementCount(), width, height, renderer, window); // PRINTING.
                        
                        // SECOND PIECE
                            futureLocation = selectPiece(board, board.getboard()[actualLocation.row][actualLocation.col]%10==2, board.getMovementCount(), width, height , renderer, window);
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
                    PawnPromotion(board, renderer);
                }


                printBoard(board, width, height, renderer, window); // PRINTING
                board.setMovementCount(board.getMovementCount()+1);

        }

        return 0;

}

int singleplayerloop(Board board, SDL_Renderer* renderer, SDL_Window* window, int width, int height, std::string filename){

    // Returns 1 (White win), -1 (Black win), 2 (Stalemate)
    // CHOOSE WHITE/BLACK white (color = 1/true), black (color = 0/false)

    importImageInRender(renderer, "assets/images/chooseColor.png", 0, 0, (width), (height));    
    importImageInRender(renderer, "assets/images/blackwhite.png", (width/3), (height/4), (width/3), (height/3));
    SDL_RenderPresent(renderer);
    bool color = true;

    bool waiting = true;

    while (waiting)
    {
    
        SDL_Point click = userInput();
        if (click.x == -1) return -1;
        int mx = click.x;
        int my = click.y;

            if (my == -1 && mx == -1)
            {
                waiting = false;
                return 0;
            }

            if(mx >= width/3 && mx <= width/3 + (width/6) && my >= height/4 && my <= height/4 + (height*2/3)){
                color = true; // player plays as white
                waiting = false;
                break;
            }else if(mx >= width/3 + (width/6) && mx <= width/3 * 2 && my >= height/4 && my <= height*2/3){
                color = false; // player plays as black
                waiting = false;
                break;
            }
    }


    bool playerMoving = color; // If the player choses white, he plays first.

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
                        return 2;
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
                        actualLocation = selectPiece(board, false, board.getMovementCount(), width, height ,renderer, window);

                        // forfeit
                        if(actualLocation.row == -2 && actualLocation.col == -2){
                            if(downloadConfirmation(renderer, width, height)){
                                board.exportGametoFile(filename);
                            }
                            if(color){ return 1; } else{ return -1; }
                        }

                    }while(!board.isPieceValid(actualLocation));


                    do{
                        printBoardAndLegitMoves(board, actualLocation, board.getMovementCount(), width, height, renderer, window); // PRINTING.
                        
                        // SECOND PIECE
                            futureLocation = selectPiece(board, board.getboard()[actualLocation.row][actualLocation.col]%10==2, board.getMovementCount(), width, height ,renderer, window);

                                // forfeit
                                if(futureLocation.row == -2 && futureLocation.col == -2){
                                    if(downloadConfirmation(renderer, width, height)){
                                        board.exportGametoFile(filename);
                                    }
                                    if(color){ return 1; } else{ return -1; }
                                }

                                // standard move

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
                        PawnPromotion(board, renderer);
                    }
                }else{ // AI MOVING (FUNCTION THAT GENERATES MOVES)
                    std::pair<T_Coordinates, T_Coordinates> bestMove = board.bestMoveWithMinimax(2, -2147483647, +2147483647);
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

    importImageInRender(renderer, "assets/images/playingBackground.png", 0, 0, width, height);

    // GET MATCH

    if(howManyGames(filename) == 0){
        return;
    }

    int matchpointer = chooseMatch(renderer, window, width, height, filename) - 1;

        if(matchpointer == -1 || matchpointer > howManyGames(filename)){
            return;
        }
        
        if(matchpointer == -3){
            emptyFile(filename);
            return;
        }


    // GET BOARD

    int boardpointer = 0; // This pointer points to the board that the user is reviewing.

    // IMPORT

    board.importGametoBoard(filename, matchpointer);

    std::vector <std::vector <int>> game = board.gethistory();


    importImageInRender(renderer, "assets/images/playingBackground.png", 0, 0, width, height); // Match background
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

            while (waiting)
            {
            
                SDL_Point click = userInput();
                int mx = click.x;
                int my = click.y;

                    if (my == -1 && mx == -1)
                    {
                        return;
                    }

                    if(mx > 600 + 10 && mx < 600 + 10 + 200 && my > 600 - 200 && my < 600 - 200 + 200){
                    boardpointer--;
                        waiting = false;
                        break;
                    }else if(mx > 600 + 210 && mx < 600 + 210 + 200 && my > 600 - 200 && my < 600 - 200 + 200){
                        boardpointer++;
                        waiting = false;
                    break;
                    }
            }

            if(boardpointer < 0 || boardpointer >= game.size()){
                break;
            }

    }        

}

void printBoard(Board board, int width, int height, SDL_Renderer *renderer, SDL_Window *window){
    
    // Board decoration.
    importImageInRender(renderer, "assets/images/playingBackground.png", 0, 0, width, height);

    // Chess board.
    board.printboard(600, 600, renderer, window);

    // Strips (A-H) and (1-8) 
    importImageInRender(renderer, "assets/images/letterBar.png", 0, 600, 600, 80);
    importImageInRender(renderer, "assets/images/numberBar.png", 600, 0, 80, 600);

    // Forfeit button
    importImageInRender(renderer, "assets/images/surrendButton.png", (width*527)/864, (height*364)/510, (width*328)/864, (height*141)/510);

    SDL_RenderPresent(renderer);
}

void printBoardAndLegitMoves(Board board, T_Coordinates pieceCoords, int movementCount, int width, int height, SDL_Renderer *renderer, SDL_Window *window){

    // Board decoration.
    importImageInRender(renderer, "assets/images/playingBackground.png", 0, 0, width, height);

    
    // Chess board.
    board.printboard(600, 600, renderer, window);

    // Strips (A-H) and (1-8) 
    importImageInRender(renderer, "assets/images/letterBar.png", 0, 600, 600, 80);
    importImageInRender(renderer, "assets/images/numberBar.png", 600, 0, 80, 600);

    // Forfeit button
    importImageInRender(renderer, "assets/images/surrendButton.png", (width*527)/864, (height*364)/510, (width*328)/864, (height*141)/510);

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

T_Coordinates selectPiece(Board board, bool kingClicked, int movementCount, int width, int height, SDL_Renderer *renderer, SDL_Window *window){

    // Returns the coordinates of the piece chosen or a special code (-1, -1) if no piece was chosen.

    bool waiting = true;

    while (waiting)
    {
        SDL_Point click = userInput();
        if (click.x == -1) return {-1, -1};
        int mx = click.x;
        int my = click.y;

            if (mx == -1 && my == -1)
            {
                waiting = false;
                T_Coordinates nullcord;
                nullcord.row = -1;
                nullcord.col = -1;
                return nullcord;

            }else{


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
                
                if(mx/75 >= 0 && mx/75 < 8 && my/75 >= 0 && my/75 < 8){ // Standard case.
                    T_Coordinates returnPiece;
                    returnPiece.col = mx / 75;
                    returnPiece.row = my / 75;
                    return returnPiece;
                }else if(mx >= (width*527)/864 && mx < (width*527)/864 + (width*328)/864 && my >= (height*364)/510 && my < (height*364)/510 + (height*141)/510){ // Forfeit button
                    T_Coordinates forfeitcord;
                    forfeitcord.row = -2;
                    forfeitcord.col = -2;
                    return forfeitcord;
                }else if(false){ // Options button (to implement)


                }else{ // Everything else
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

T_Coordinates nullcord;
nullcord.row = -1;
nullcord.col = -1;
return nullcord;

}

bool isNullCoord(T_Coordinates Coord){

    // Returns if the cordinate is null or not.

    return (Coord.col == -1 && Coord.row == -1);

}

int howManyGames(std::string filename){

    // Returns how many games does the file have.

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

    // It returns the match chosen by the user (1-10, not 0-9).


    // PRINTING ON THE SCREEN
    importImageInRender(renderer, "assets/images/ChooseGameBackground.png", 0, 0, width, height);
    importImageInRender(renderer, "assets/images/deleteFiles.png", width - std::max(20, width/64) - std::max(100, std::min(width/8, height/8)), height - std::max(20, width/64) - std::max(100, std::min(width/8, height/8)), std::max(100, std::min(width/8, height/8)), std::max(100, std::min(width/8, height/8)));

    int ngames = howManyGames(filename);

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


    // TAKING USER INPUT

    bool waiting = true;

    while (waiting)
    {

        SDL_Point click = userInput();
        if (click.x == -1) return -1;
        int mx = click.x;
        int my = click.y;
        
            if (mx == -1 && my == -1)
            {
                return -1;
            }
            else
            {

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
                else if(mx >= width - std::max(20, width/64) - std::max(100, std::min(width/8, height/8)) && mx < width - std::max(20, width/64) &&
                    my >= height - std::max(20, width/64) - std::max(100, std::min(width/8, height/8)) && my < height - std::max(20, width/64)) {
                    return -2;
                }
            }
    }

    return 0;
}

bool downloadConfirmation(SDL_Renderer* renderer, int width, int height){
    
    // It returns if the user wants to store the game in the file or not.
    
    importImageInRender(renderer, "assets/images/downloadboard.png", width/2 - 200, height/2 - 200, 400, 400);
    importImageInRender(renderer, "assets/images/yes.png", width/2 - 200, height/2 + 50, 100, 100);
    importImageInRender(renderer, "assets/images/no.png", width/2 +  50, height/2 + 50, 100, 100);
    SDL_RenderPresent(renderer);

    bool waiting = true;


    while (waiting)
    {
        SDL_Point click = userInput();
        if (click.x == -1) return -1;
        int mx = click.x;
        int my = click.y;

            if (mx == -1 && my == -1)
            {
                return -1;
            }
            else
            {
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

    return false;
}

void PawnPromotion(Board& board, SDL_Renderer* renderer){

    T_Coordinates pawnCoords{-1, -1};
    int movementCount = board.getMovementCount();

    if(movementCount%2==0){
        for(int i = 0; i < 8; i++){
            if(board.getboard()[0][i]%10==1){
                pawnCoords.row = 0;
                pawnCoords.col = i;
                break;
            }
        }
    }else{
        for(int i = 0; i < 8; i++){
            if(board.getboard()[7][i]%10==1){
                pawnCoords.row = 7;
                pawnCoords.col = i;
                break;
            }
        }       
    }

    if(pawnCoords.row >= 0){
        if(movementCount%2==0){ // WHITE PIECES

            int x = pawnCoords.col * 75;
            int y = pawnCoords.row * 75;
            int w = 75; 
            int h = 300;

            importImageInRender(renderer, "assets/images/pawnpromotion.png", x, y, w, h);
            SDL_RenderPresent(renderer);

            bool promotion = false;
            while (!promotion) {

                SDL_Point click = userInput();
                int mx = click.x;
                int my = click.y;
        
                if (mx == -1 && my == -1){
                    
                }else{
                    if (mx >= x && mx < x + w && my >= y && my < y + h) {
                        switch(my/75){
                            case 0: 
                                board.PawnPromotion(pawnCoords, (((board.getboard()[pawnCoords.row][pawnCoords.col]/10)*10)+3));    // QUEEN
                                promotion = true;
                                break;
                            case 1:
                                board.PawnPromotion(pawnCoords, (((board.getboard()[pawnCoords.row][pawnCoords.col]/10)*10)+6));    // KNIGHT
                                promotion = true;
                                break;
                            case 2:
                                board.PawnPromotion(pawnCoords, ((board.getboard()[pawnCoords.row][pawnCoords.col]/10)*10)+4);    // ROOK
                                promotion = true;
                                break;
                            case 3:
                                board.PawnPromotion(pawnCoords, (((board.getboard()[pawnCoords.row][pawnCoords.col]/10)*10)+5));    // BISHOP
                                promotion = true;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

        }else{ // BLACK PIECES

            int x = pawnCoords.col * 75;
            int y = (pawnCoords.row - 3) * 75; // To adjust to the display.
            int w = 100; 
            int h = 300;

            importImageInRender(renderer, "assets/images/pawnpromotion.png", x, y, w, h);
            SDL_RenderPresent(renderer);

            bool promotion = false;
            while (!promotion) {

                SDL_Point click = userInput();
                int mx = click.x;
                int my = click.y;
        
                if (mx == -1 && my == -1){
                    
                }else{
                    if (mx >= x && mx < x + w && my >= y && my < y + h) {
                        switch(my/75){
                            case 4: 
                                board.PawnPromotion(pawnCoords,((board.getboard()[pawnCoords.row][pawnCoords.col]/10)*10)+3);    // QUEEN
                                promotion = true;
                                break;
                            case 5:
                                board.PawnPromotion(pawnCoords, ((board.getboard()[pawnCoords.row][pawnCoords.col]/10)*10)+6);    // KNIGHT
                                promotion = true;
                                break;
                            case 6:
                                board.PawnPromotion(pawnCoords, ((board.getboard()[pawnCoords.row][pawnCoords.col]/10)*10)+4);    // ROOK
                                promotion = true;
                                break;
                            case 7:
                                board.PawnPromotion(pawnCoords, ((board.getboard()[pawnCoords.row][pawnCoords.col]/10)*10)+5);    // BISHOP
                                promotion = true;
                                break;
                            default:
                                break;
                        }
                    }
                }
            }

        }
        }
}

void emptyFile(std::string filename){
    std::ofstream ofs(filename, std::ios::trunc);
}   

/* 
TODO: 
(X) Make a surrender button
(X) Unify all the input user code as a function that returns the mx and my
() Include options.
(X) ERASE GAMES FROM FILE function (especial output for choose match then special action then special action in review games)
() USE width and height consistently (I think some methods/functions use pixels directly)
() Maybe turn the main.cc into a class?
() WRITE DOCUMENTATION


*/
    