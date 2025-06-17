#include "include/utils.h"
#include "include/board.h"
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>

Board::Board(){

    int chessBoard[8][8] = {
        {04, 06, 05, 03, 02, 05, 06, 04},
        {01, 01, 01, 01, 01, 01, 01, 01},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {11, 11, 11, 11, 11, 11, 11, 11},
        {14, 16, 15, 13, 12, 15, 16, 14}
    };

    setboard(chessBoard);

}

void Board::setboard(int board[8][8]){

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            this->board[i][j] = board[i][j];
        }
    }

}

void Board::printboard(int width, int height, SDL_Renderer *renderer, SDL_Window *window) {   

    SDL_Rect rect;
    int blockwidth = width / 8;
    int blockheight = height / 8;

    //This function displays the current state of the board.

    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
                if ((i + j) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // blanco
                }else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // negro
                }
                   
                rect.x = i * blockwidth;
                rect.y = j * blockheight;
                rect.w = blockwidth;
                rect.h = blockheight;
                SDL_RenderFillRect(renderer, &rect);
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (board[i][j] % 10) {
                case 0:  
                    // Casilla vacía
                    break;
                case 1:  
                    // Peón
                    if ((i + j) % 2 == 0) {
                        importImageInRender(renderer, "assets/images/whitepawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/whitepawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                case 2:  
                    // Rey
                    if ((i + j) % 2 == 0) {
                        importImageInRender(renderer, "assets/images/whitepawn.png",  j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/whitepawn.png",  j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                case 3:  
                    // Reina
                    if ((i + j) % 2 == 0) {
                        importImageInRender(renderer, "assets/images/whitepawn.png",  j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/whitepawn.png",  j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                case 4:  
                    // Torre
                    if ((i + j) % 2 == 0) {
                        importImageInRender(renderer, "assets/images/whitepawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/whitepawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                case 5:  
                    // Alfil
                    if ((i + j) % 2 == 0) {
                        importImageInRender(renderer, "assets/images/whitepawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/whitepawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                case 6:  
                    // Caballo
                    if ((i + j) % 2 == 0) {
                        importImageInRender(renderer, "assets/images/whitepawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/whitepawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                default: 
                    // Pieza desconocida
                    break;
            }
        }
    }

    SDL_RenderPresent(renderer);
 
}

void Board::updateboard(T_Coordinates actualLocation, T_Coordinates futurelocation){

    //This function modifies the board state based on the player's move.

    board[futurelocation.row][futurelocation.col] = board[actualLocation.row][actualLocation.col];
    board[actualLocation.row][actualLocation.col] = 0;


}

void Board::isThreatened(int movementCount, T_Coordinates actualLocation, T_Coordinates futurelocation, bool &isItThreatened){

    isItThreatened = false;

    //This function checks if a square of the board is threteaned by a piece, by taking as input a particular movement (with the actual location and the future location)
    //and returns the condition isItThreatened with wether or not the square can be considered threatened.

    //If the piece is not a pawn, then the condition "threatened" is equal to the condition "legit",thus if the piece is not a pawn, then isItThreatened is equal to isItLegit:

    if(board[actualLocation.row][actualLocation.col] % 10 == 2 ||
            board[actualLocation.row][actualLocation.col] % 10 == 3 || 
            board[actualLocation.row][actualLocation.col] % 10 == 4 ||
            board[actualLocation.row][actualLocation.col] % 10 == 5 ||
            board[actualLocation.row][actualLocation.col] % 10 == 6){

                isLegit(movementCount, actualLocation, futurelocation, isItThreatened);
            }


    //Now, if the piece is a pawn, some special rules need to be added.

    //GENERAL CHECK for pawns:


    if(actualLocation.col > 7 || actualLocation.col < 0 || actualLocation.row > 7 || actualLocation.row < 0){
        isItThreatened = false;
        return;
    }

    if(futurelocation.col > 7 || futurelocation.col < 0 || futurelocation.row > 7 || futurelocation.row < 0){
        isItThreatened = false;
        return;
    }


    if(actualLocation.col == futurelocation.col && actualLocation.row == futurelocation.row){
        isItThreatened = false;
        return;
    }

    if((board[actualLocation.row][actualLocation.col] % 10) == 0){
        isItThreatened = false;
        return;
    }


    if((movementCount % 2 == 0 && (board[actualLocation.row][actualLocation.col] / 10) == 0) ||
    (movementCount % 2 != 0 && (board[actualLocation.row][actualLocation.col] / 10) == 1)){

        isItThreatened = false;
        return;

    }


    if(movementCount % 2 == 0 && board[futurelocation.row][futurelocation.col] / 10 == 1 ||
    movementCount % 2 != 0 && board[futurelocation.row][futurelocation.col] / 10 == 0 && 
    board[futurelocation.row][futurelocation.col] % 10 != 0){

        isItThreatened = false;
        return;

    }

    //SPECIAL RULES.
    //The position is threatened by a pawn only if its diagonal

    int dx = futurelocation.col - actualLocation.col;
    int dy = futurelocation.row - actualLocation.row;


    if(board[actualLocation.row][actualLocation.col] % 10 == 1){
        //White pawns
        if(board[actualLocation.row][actualLocation.col] / 10 == 1){
            if((dx == 1 || dx == -1) && dy == -1){
                isItThreatened = true;
            }

        //Black pawns
        }else{
            if((dx == 1 || dx == -1) && dy == 1){
                isItThreatened = true;
            }


        }
    }
}

void Board::isLegit(int movementCount, T_Coordinates actualLocation, T_Coordinates futurelocation, bool &isItLegit){


    //This function checks whether the move is legitimate or not.

    //FIRST PHASE: GENERAL CHECK.

    //Now we are going to check some general cases, and if the moves break any of the general rules (such as moving a opponents piece)
    // Is the piece moving to a valid place? 

    if(actualLocation.col > 7 || actualLocation.col < 0 || actualLocation.row > 7 || actualLocation.row < 0){
        isItLegit = false;
        return;
    }

    if(futurelocation.col > 7 || futurelocation.col < 0 || futurelocation.row > 7 || futurelocation.row < 0){
        isItLegit = false;
        return;
    }

    // Is the piece moving at all?

    if(actualLocation.col == futurelocation.col && actualLocation.row == futurelocation.row){
        isItLegit = false;
        return;
    }
    // Does the piece exist?

    if((board[actualLocation.row][actualLocation.col] % 10) == 0){
        isItLegit = false;
        return;
    }

    // Is the user moving the right color piece? (If movementCount is even then the piece must be white and if it is odd the piece must be black)

    if((movementCount % 2 == 0 && (board[actualLocation.row][actualLocation.col] / 10) == 0) ||
    (movementCount % 2 != 0 && (board[actualLocation.row][actualLocation.col] / 10) == 1)){

        isItLegit = false;
        return;

    }

    // Is the piece moving to a square occupied by a piece of its own color?

    if(movementCount % 2 == 0 && board[futurelocation.row][futurelocation.col] / 10 == 1 ||
    movementCount % 2 != 0 && board[futurelocation.row][futurelocation.col] / 10 == 0 && 
    board[futurelocation.row][futurelocation.col] % 10 != 0){

        isItLegit = false;
        return;

    }

    //SECOND PHASE: SPECIFIC CHECK.
    isItLegit = false;

    int dx = futurelocation.col - actualLocation.col;
    int dy = futurelocation.row - actualLocation.row;

    // WHITE PAWNS (Moving up the board)
    if (board[actualLocation.row][actualLocation.col] % 10 == 1 && movementCount % 2 == 0) {
        if ((dx == 0 && dy == -1 && board[futurelocation.row][futurelocation.col] / 10 == 0) ||  // Forward one step
            (dx == 0 && dy == -2 && actualLocation.row == 6 &&  // Double step from start
            board[futurelocation.row][futurelocation.col] / 10 == 0 &&
            board[actualLocation.row - 1][actualLocation.col] / 10 == 0) ||
            ((dx == 1 || dx == -1) && dy == -1 && board[futurelocation.row][futurelocation.col] / 10 == 0)){ // Capturing diagonally
            
            isItLegit = true;
        }
        return;
    }

    // BLACK PAWNS (Moving down the board)
    if (board[actualLocation.row][actualLocation.col] % 10 == 1 && movementCount % 2 != 0) {
        if ((dx == 0 && dy == 1 && board[futurelocation.row][futurelocation.col] / 10 == 0) ||  // Forward one step
            (dx == 0 && dy == 2 && actualLocation.row == 1 &&  // Double step from start
            board[futurelocation.row][futurelocation.col] / 10 == 0 &&
            board[actualLocation.row + 1][actualLocation.col] / 10 == 0) ||
            ((dx == 1 || dx == -1) && dy == 1 && board[futurelocation.row][futurelocation.col] / 10 != 0)) { // Capturing diagonally

            isItLegit = true;
        }
        return;
    }

    // KING (moving everywhere)
    if(board[actualLocation.row][actualLocation.col] % 10 == 2){
        if(dx >= -1 && dx <= 1 && dy >= -1 && dy <= 1){
            isItLegit = true;
            return;
        }
    }

    // KNIGHT (moving in L)
    if (board[actualLocation.row][actualLocation.col] % 10 == 6) { 
        if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
            isItLegit = true;
            return;
        }
    }

    // ROOK (moving straight)

    if(board[actualLocation.row][actualLocation.col] % 10 == 4){

    if((dx != 0 && dy == 0) || (dx == 0 && dy != 0)){

    if(dx == 1 || dx == -1 || dy == 1 || dy == -1){
        isItLegit = true;
        return;
    }


    //#1 (The rook is moving to the right)
    if(dx > 0){
        for(int i = actualLocation.col + 1; i < futurelocation.col; i++){
            if((board[actualLocation.row][i] % 10) == 0){              
                isItLegit = true;
            }else{
                isItLegit = false;
                return;
            }
        }

    //#2 (The rook is moving to the left)
    }else if(dx < 0){
        for(int i = futurelocation.col + 1; i < actualLocation.col; i++){
            if((board[actualLocation.row][i] % 10) == 0){                      
                isItLegit = true;
            }else{
                isItLegit = false;
                return;
            }
        }
    }


    // vertical movement
    //#3 (The rook is moving down)
    if(dy > 0){
        for(int j = actualLocation.row + 1; j < futurelocation.row; j++){
            if((board[j][actualLocation.col] % 10) == 0){                         
                isItLegit = true;
            }else{
                isItLegit = false;
                return;
            }
    //#4(The rook is moving up)

        }
        
        }else if(dy < 0){
        for(int j = actualLocation.row - 1; j > futurelocation.row; j--){
            if((board[j][actualLocation.col] % 10) == 0){                        
                isItLegit = true;
            }else{
                isItLegit = false;
                return;
            }
        }
    }
    }
    }

    // BISHOP (moving diagonally)

    if(board[actualLocation.row][actualLocation.col] % 10 == 5){

    if(abs(dx) == abs(dy)){

    if(abs(dx) == 1){
        isItLegit = true;
        return;
    } 

    //#1: moving to the second quadrant
        if(dx < 0 && dy < 0){
            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row + i][futurelocation.col + i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return;
                }
            }
    //#2: moving to the first quadrant

        } else if(dx > 0 && dy < 0){

            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row + i][futurelocation.col - i] == 0){   
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return;
                }
            }
    //#3: moving to the third quadrant

        } else if(dx < 0 && dy > 0){
            
            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row - i][futurelocation.col + i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return;
                }
            }
    //#4: moving to the fourth quadrant

        } else if(dx > 0 && dy > 0){

            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row - i][futurelocation.col - i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return;
                }
            }

        }

    }else{
        isItLegit = false;
        return;
    }
    }


    //QUEEN (moving both diagonaly and straight)

    if(board[actualLocation.row][actualLocation.col] % 10 == 3){

        //If its moving like a rook (same code).


    if((dx != 0 && dy == 0) || (dx == 0 && dy != 0)){

    if(dx == 1 || dx == -1 || dy == 1 || dy == -1){
        isItLegit = true;
        return;
    }


    if(dx > 0){
        for(int i = actualLocation.col + 1; i < futurelocation.col; i++){
            if((board[actualLocation.row][i] % 10) == 0){              
                isItLegit = true;
            }else{
                isItLegit = false;
                return;
            }
        }

    }else if(dx < 0){
        for(int i = futurelocation.col + 1; i < actualLocation.col; i++){
            if((board[actualLocation.row][i] % 10) == 0){                      
                isItLegit = true;
            }else{
                isItLegit = false;
                return;
            }
        }
    }

    if(dy > 0){
        for(int j = actualLocation.row + 1; j < futurelocation.row; j++){
            if((board[j][actualLocation.col] % 10) == 0){                         
                isItLegit = true;
            }else{
                isItLegit = false;
                return;
            }
            }
    

        }else if(dy < 0){
        for(int j = actualLocation.row - 1; j > futurelocation.row; j--){
            if((board[j][actualLocation.col] % 10) == 0){                        
                isItLegit = true;
            }else{
                isItLegit = false;
                return;
            }
        }
    }
    }

        
        //If its moving like a bishop (same code).

    if(abs(dx) == abs(dy)){

    if(abs(dx) == 1){
        isItLegit = true;
        return;
    } 

        if(dx < 0 && dy < 0){
            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row + i][futurelocation.col + i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return;
                }
            }

        } else if(dx > 0 && dy < 0){

            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row + i][futurelocation.col - i] == 0){   
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return;
                }
            }

        } else if(dx < 0 && dy > 0){

            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row - i][futurelocation.col + i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return;
                }
            }

        } else if(dx > 0 && dy > 0){

            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row - i][futurelocation.col - i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return;
                }
            }

        }

    }

    }


}

void Board::prohibitedMoves( int movementCount, T_Coordinates prohibitedSquares[4096], int &nsquares){


    //This function takes the board and the movementCount and generates a list of squares where the king corresponding to the current colour cant go.


    bool isItLegit;

    int nblackprohibitedmoves = 0;
    int nwhiteprohibitedmoves = 0;

    int nextMovementCount = movementCount + 1;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(movementCount % 2 != 0 && board[i][j] / 10 == 1 && board[i][j] % 10 != 0){    //black's moving & the piece is white...

                

                for(int k = 0; k < 8; k++){
                    for(int t = 0; t < 8; t++){ //... the program checks every possible move for that piece...

                        T_Coordinates actualLocation;
                        actualLocation.row = i;
                        actualLocation.col = j;
                        
                        T_Coordinates futurelocation;
                        futurelocation.row = k;
                        futurelocation.col = t;

                        isThreatened(nextMovementCount, actualLocation, futurelocation, isItLegit);  //... checks if its legit or not...

                        if(isItLegit){
                            prohibitedSquares[nblackprohibitedmoves].row = futurelocation.row;
                            prohibitedSquares[nblackprohibitedmoves].col = futurelocation.col;    // ...and the legit ones are saved in an array.
                            nblackprohibitedmoves = nblackprohibitedmoves + 1;
                        }



                    }
                }


            } else if(movementCount % 2 == 0 && board[i][j] / 10 == 0 && board[i][j] % 10 != 0){ //white's moving & the piece is black

                
                for(int k = 0; k < 8; k++){
                    for(int t = 0; t < 8; t++){ //... the program checks every possible move for that piece...

                        T_Coordinates actualLocation;
                        actualLocation.row = i;
                        actualLocation.col = j;

                        T_Coordinates futurelocation;
                        futurelocation.row = k;
                        futurelocation.col = t;
                        
                        isThreatened(nextMovementCount, actualLocation, futurelocation, isItLegit);  //... checks if its legit or not...

                        if(isItLegit){
                            prohibitedSquares[nwhiteprohibitedmoves].row = futurelocation.row;
                            prohibitedSquares[nwhiteprohibitedmoves].col = futurelocation.col;    // ...and the legit ones are saved in an array.
                            nwhiteprohibitedmoves = nwhiteprohibitedmoves + 1;
                        }

                    }
                }




            } 
        }
    }

    //As only one thing can be true (wether the black king is moving or the white king is moving), the nsquares variable returns the number of squares prohibited
    //corresponding only to the king that is moving.

    if(nwhiteprohibitedmoves != 0){
        nsquares = nwhiteprohibitedmoves;
    }else{
        nsquares = nblackprohibitedmoves;
    }

    }

void Board::isTheKingChecked(int movementCount, T_Coordinates prohibitedSquares[4096], int nsquares, bool &checked){

    //This function checks wether the king is checked or not.

    checked = false;

    int kingrow;
    int kingcol;

    //We locate the king of the corresponding color

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] % 10 == 2 &&((board[i][j] / 10 == 0 && movementCount % 2 != 0)||
            (board[i][j] / 10 == 1 && movementCount % 2 == 0))){                                
                
                kingrow = i;
                kingcol = j;

            }
        }
    }

    //Then check if the king is in any of the checked positions.

    for(int k = 0; k < nsquares; k++){
        if(prohibitedSquares[k].row == kingrow && prohibitedSquares[k].col == kingcol){
            checked = true;
        }   
    }


}

void Board::isTheKingCheckMated(int movementCount, T_Coordinates prohibitedSquares[4096], bool &matchOver){

    //This function checks if there exists a legal move such that the king is not in check. It can therefore indicate two different situations:

    // If its executed with the king being in check and it returns "true" in the value matchOver, it means that the king is checkmated, and it means a victory for the opposing player. 
    // If its executed with the king NOT being in check and it returns "true" in the value matchOver, it means a Stalemate, and therefore a draw. 

    bool isItThreatened;
    bool checked;
    int nsquares;
    T_Coordinates prohibitedSquaresD[4096];
    int savingMoves = 0;

    //The function must check if there is any legal move that can save the king ¿How?.
    //Well using the function isTheKingChecked and prohibitedMoves we can calculate if there is any legal move that makes the king NOT checked in the next move. 


    //To do that, we duplicate the chess board for trials (to try every possible move)

    Board board2;


    board2.setboard(board);


    //Then the magic comes. We check every piece.

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(movementCount % 2 == 0 && board[i][j] / 10 == 1 && board[i][j] % 10 != 0){    //If white is moving & the piece is white (which means that white is checked)...            

                for(int k = 0; k < 8; k++){
                    for(int t = 0; t < 8; t++){ //... the program checks every possible move for that piece...

                        board2.setboard(board);

                        T_Coordinates actualLocation;
                        actualLocation.row = i;
                        actualLocation.col = j;
                        T_Coordinates futurelocation;
                        futurelocation.row = k;
                        futurelocation.col = t;

                        isThreatened(movementCount, actualLocation, futurelocation, isItThreatened);  //... and checks if its legit or not.
                    

                        if(isItThreatened){ //If the movement is legit... 
                            board2.updateboard(actualLocation, futurelocation); //... we perform it in a duplicated board... 
                            board2.prohibitedMoves(movementCount, prohibitedSquaresD, nsquares); //... we calculate the checked squares in that duplicate board..
                            board2.isTheKingChecked(movementCount, prohibitedSquaresD, nsquares, checked); //... and we look if the king is still checked.

                            if(checked == false){ //if there is at least one legal move where the king is still not checked, the king is not checkmated.
                                matchOver = false;
                                savingMoves = savingMoves + 1;
                                return;
                            }
                        }



                    }
                }


            } else if(movementCount % 2 != 0 && board[i][j] / 10 == 0 && board[i][j] % 10 != 0){ //If black is moving & the piece is black (which means that black is checked)...

                for(int k = 0; k < 8; k++){
                    for(int t = 0; t < 8; t++){ //... the program checks every possible move for that piece...

                        T_Coordinates actualLocation;
                        actualLocation.row = i;
                        actualLocation.col = j;
                        T_Coordinates futurelocation;
                        futurelocation.row = k;
                        futurelocation.col = t;


                        board2.setboard(board);

                        isThreatened(movementCount, actualLocation, futurelocation, isItThreatened);  //... and checks if its legit or not.
                    

                        if(isItThreatened){ //If the movement is legit... 
                            board2.updateboard(actualLocation, futurelocation); //... we perform it in a duplicated board... 
                            board2.prohibitedMoves(movementCount, prohibitedSquaresD, nsquares); //... we calculate the checked squares in that duplicate board..
                            board2.isTheKingChecked(movementCount, prohibitedSquaresD, nsquares, checked); //... and we look if the king is still checked.

                            if(checked == false){ //if there is at least one legal move where the king is still not checked, the king is not checkmated.
                                matchOver = false;
                                savingMoves = savingMoves + 1;
                                return;

                            }
                        }

                        }
                    }
                } 
            }
    }
        
        if(savingMoves == 0){
            matchOver = true;
        }

}

void Board::PawnPromotion(bool &change, char language){

    char piece = 'Q';

    for (int i = 0; i < 8; i++) {
        if (board[0][i] % 10 == 1) {
            change = true;
            do {
                printf("%s", (language == 's') ? "\n¿Que quieres cambiar por tu peón? Reina (Q), Caballo (N), Torre(R), Alfil (B): " : "\nWhat do you want to trade your pawn for? Queen (Q), Knight (N), Rook(R), Bishop (B): ");
                scanf(" %c", &piece);
                printf("\n");

                if (piece != 'Q' && piece != 'R' && piece != 'N' && piece != 'B') {
                    printf("%s", (language == 's') ? "\nPor favor, introduce una pieza válida.\n" : "\nPlease introduce a valid piece\n");
                }

            } while (piece != 'Q' && piece != 'R' && piece != 'N' && piece != 'B');

            switch (piece) {
                case 'Q':
                    board[0][i] = 13;
                    break;
                case 'B':
                    board[0][i] = 15;
                    break;
                case 'N':
                    board[0][i] = 16;
                    break;
                case 'R':
                    board[0][i] = 14;
                    break;
            }
        }
    }

    for (int j = 0; j < 8; j++) {
        if (board[7][j] % 10 == 1) {
            change = true;
            do {
                printf("%s", (language == 's') ? "\nQue quieres cambiar por tu peón: Reina (Q), Caballo (N), Torre(R), Alfil (B)\n" : "\nWhat do you want to trade your pawn for: Queen (Q), Knight (N), Rook(R), Bishop (B)\n");
                scanf(" %c", &piece);
                printf("\n");

                if (piece != 'Q' && piece != 'R' && piece != 'N' && piece != 'B') {
                    printf("%s", (language == 's') ? "\nPor favor, introduce una pieza válida.\n" : "\nPlease introduce a valid piece\n");
                }

            } while (piece != 'Q' && piece != 'R' && piece != 'N' && piece != 'B');

            switch (piece) {
                case 'Q':
                    board[7][j] = 3;
                    break;
                case 'B':
                    board[7][j] = 5;
                    break;
                case 'N':
                    board[7][j] = 6;
                    break;
                case 'R':
                    board[7][j] = 4;
                    break;
            }
        }
    }

}