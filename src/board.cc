#include "include/utils.h"
#include "include/board.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SDL2/SDL.h>

Board::Board(){

    int chessBoard[8][8] = {
        {4, 6, 5, 3, 2, 5, 6, 4},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {11, 11, 11, 11, 11, 11, 11, 11},
        {14, 16, 15, 13, 12, 15, 16, 14}
    };

    setboard(chessBoard);

}

Board::Board(int board[8][8]){

    setboard(board);

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
                    if ((board[i][j])/10 != 0) {
                        importImageInRender(renderer, "assets/images/whitepawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/blackpawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                case 2:  
                    // Rey
                    if ((board[i][j])/10 != 0) {
                        importImageInRender(renderer, "assets/images/whiteking.png",  j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/blackking.png",  j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                case 3:  
                    // Reina
                    if ((board[i][j])/10 != 0) {
                        importImageInRender(renderer, "assets/images/whitequeen.png",  j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/blackqueen.png",  j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                case 4:  
                    // Torre
                    if ((board[i][j])/10 != 0) {
                        importImageInRender(renderer, "assets/images/whiterook.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/blackrook.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                case 5:  
                    // Alfil
                    if ((board[i][j])/10 != 0) {
                        importImageInRender(renderer, "assets/images/whitebishop.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/blackbishop.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                case 6:  
                    // Caballo
                    if ((board[i][j])/10 != 0) {
                        importImageInRender(renderer, "assets/images/whiteknight.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    } else {
                        importImageInRender(renderer, "assets/images/blackknight.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                    }
                    break;
                default: 
                    // Pieza desconocida
                    break;
            }
        }
    }
 
}

void Board::updateboard(T_Coordinates actualLocation, T_Coordinates futurelocation){

    //This function modifies the board state based on the player's move.

    board[futurelocation.row][futurelocation.col] = board[actualLocation.row][actualLocation.col];
    board[actualLocation.row][actualLocation.col] = 0;


}

bool Board::isThreatened(int movementCount, T_Coordinates actualLocation, T_Coordinates futurelocation){

    bool isItThreatened = false;

    //This function checks if a square of the board is threteaned by a piece, by taking as input a particular movement (with the actual location and the future location)
    //and returns the condition isItThreatened with wether or not the square can be considered threatened.

    //If the piece is not a pawn, then the condition "threatened" is equal to the condition "legit",thus if the piece is not a pawn, then isItThreatened is equal to isItLegit:

    if(board[actualLocation.row][actualLocation.col] % 10 == 2 ||
            board[actualLocation.row][actualLocation.col] % 10 == 3 || 
            board[actualLocation.row][actualLocation.col] % 10 == 4 ||
            board[actualLocation.row][actualLocation.col] % 10 == 5 ||
            board[actualLocation.row][actualLocation.col] % 10 == 6){

                isItThreatened = isLegit(movementCount, actualLocation, futurelocation);
            }


    //Now, if the piece is a pawn, some special rules need to be added.

    //GENERAL CHECK for pawns:


    if(actualLocation.col > 7 || actualLocation.col < 0 || actualLocation.row > 7 || actualLocation.row < 0){
        return false;
    }

    if(futurelocation.col > 7 || futurelocation.col < 0 || futurelocation.row > 7 || futurelocation.row < 0){
        return false;
    }


    if(actualLocation.col == futurelocation.col && actualLocation.row == futurelocation.row){
        return false;
    }

    if((board[actualLocation.row][actualLocation.col] % 10) == 0){
        return false;
    }


    if((movementCount % 2 == 0 && (board[actualLocation.row][actualLocation.col] / 10) == 0) ||
    (movementCount % 2 != 0 && (board[actualLocation.row][actualLocation.col] / 10) == 1)){
         return false;
    }


    if(movementCount % 2 == 0 && board[futurelocation.row][futurelocation.col] / 10 == 1 ||
    movementCount % 2 != 0 && board[futurelocation.row][futurelocation.col] / 10 == 0 && 
    board[futurelocation.row][futurelocation.col] % 10 != 0){
        return false;
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

    return isItThreatened;
}

bool Board::isLegit(int movementCount, T_Coordinates actualLocation, T_Coordinates futurelocation){

    bool isItLegit = false;

    //This function checks whether the move is legitimate or not.

    //FIRST PHASE: GENERAL CHECK.

    //Now we are going to check some general cases, and if the moves break any of the general rules (such as moving a opponents piece)
    // Is the piece moving to a valid place? 

    if(actualLocation.col > 7 || actualLocation.col < 0 || actualLocation.row > 7 || actualLocation.row < 0){
        return false;
    }

    if(futurelocation.col > 7 || futurelocation.col < 0 || futurelocation.row > 7 || futurelocation.row < 0){
        return false;
    }

    // Is the piece moving at all?

    if(actualLocation.col == futurelocation.col && actualLocation.row == futurelocation.row){
        return false;
    }
    // Does the piece exist?

    if((board[actualLocation.row][actualLocation.col] % 10) == 0){
        return false;
    }

    // Is the user moving the right color piece? (If movementCount is even then the piece must be white and if it is odd the piece must be black)

    if((movementCount % 2 == 0 && (board[actualLocation.row][actualLocation.col] / 10) == 0) ||
    (movementCount % 2 != 0 && (board[actualLocation.row][actualLocation.col] / 10) == 1)){

        return false;


    }

    // Is the piece moving to a square occupied by a piece of its own color?

    if(movementCount % 2 == 0 && board[futurelocation.row][futurelocation.col] / 10 == 1 ||
    movementCount % 2 != 0 && board[futurelocation.row][futurelocation.col] / 10 == 0 && 
    board[futurelocation.row][futurelocation.col] % 10 != 0){

        return false;


    }

    //SECOND PHASE: SPECIFIC CHECK.
    isItLegit = false;

    int dx = futurelocation.col - actualLocation.col;
    int dy = futurelocation.row - actualLocation.row;

    // WHITE PAWNS (Moving up the board)
    if (board[actualLocation.row][actualLocation.col] % 10 == 1 && movementCount % 2 == 0) {
        if ((dx == 0 && dy == -1 && board[futurelocation.row][futurelocation.col] % 10 == 0) ||
            (dx == 0 && dy == -2 && actualLocation.row == 6 &&
            board[futurelocation.row][futurelocation.col] % 10 == 0 &&
            board[actualLocation.row - 1][actualLocation.col] % 10 == 0) ||
            ((dx == 1 || dx == -1) && dy == -1 &&
            board[futurelocation.row][futurelocation.col] % 10 != 0 &&
            board[futurelocation.row][futurelocation.col] / 10 == 0)) {
            isItLegit = true;
        }
        return isItLegit;
    }

    // BLACK PAWNS (Moving down the board)
    if (board[actualLocation.row][actualLocation.col] % 10 == 1 && movementCount % 2 != 0) {
        if ((dx == 0 && dy == 1 && board[futurelocation.row][futurelocation.col] % 10 == 0) ||
            (dx == 0 && dy == 2 && actualLocation.row == 1 &&
            board[futurelocation.row][futurelocation.col] % 10 == 0 &&
            board[actualLocation.row + 1][actualLocation.col] % 10 == 0) ||
            ((dx == 1 || dx == -1) && dy == 1 &&
            board[futurelocation.row][futurelocation.col] % 10 != 0 &&
            board[futurelocation.row][futurelocation.col] / 10 != 0)) {
            isItLegit = true;
        }
        return isItLegit;
    }

    // KING (moving everywhere)
    if(board[actualLocation.row][actualLocation.col] % 10 == 2){
        if(dx >= -1 && dx <= 1 && dy >= -1 && dy <= 1){
            isItLegit = true;
            return isItLegit;
        }
    }

    // KNIGHT (moving in L)
    if (board[actualLocation.row][actualLocation.col] % 10 == 6) { 
        if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
            isItLegit = true;
            return isItLegit;
        }
    }

    // ROOK (moving straight)

    if(board[actualLocation.row][actualLocation.col] % 10 == 4){

    if((dx != 0 && dy == 0) || (dx == 0 && dy != 0)){

    if(dx == 1 || dx == -1 || dy == 1 || dy == -1){
        isItLegit = true;
        return isItLegit;
    }


    //#1 (The rook is moving to the right)
    if(dx > 0){
        for(int i = actualLocation.col + 1; i < futurelocation.col; i++){
            if((board[actualLocation.row][i] % 10) == 0){              
                isItLegit = true;
            }else{
                isItLegit = false;
                return isItLegit;
            }
        }

    //#2 (The rook is moving to the left)
    }else if(dx < 0){
        for(int i = futurelocation.col + 1; i < actualLocation.col; i++){
            if((board[actualLocation.row][i] % 10) == 0){                      
                isItLegit = true;
            }else{
                isItLegit = false;
                return isItLegit;
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
                return isItLegit; 
            }
    //#4(The rook is moving up)

        }
        
        }else if(dy < 0){
        for(int j = actualLocation.row - 1; j > futurelocation.row; j--){
            if((board[j][actualLocation.col] % 10) == 0){                        
                isItLegit = true;
            }else{
                isItLegit = false;
                return isItLegit;
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
        return  isItLegit;
    } 

    //#1: moving to the second quadrant
        if(dx < 0 && dy < 0){
            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row + i][futurelocation.col + i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return isItLegit;
                }
            }
    //#2: moving to the first quadrant

        } else if(dx > 0 && dy < 0){

            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row + i][futurelocation.col - i] == 0){   
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return isItLegit;
                }
            }
    //#3: moving to the third quadrant

        } else if(dx < 0 && dy > 0){
            
            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row - i][futurelocation.col + i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return isItLegit;
                }
            }
    //#4: moving to the fourth quadrant

        } else if(dx > 0 && dy > 0){

            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row - i][futurelocation.col - i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return isItLegit;
                }
            }

        }

    }else{
        isItLegit = false;
        return isItLegit;
    }
    }


    //QUEEN (moving both diagonaly and straight)

    if(board[actualLocation.row][actualLocation.col] % 10 == 3){

        //If its moving like a rook (same code).


    if((dx != 0 && dy == 0) || (dx == 0 && dy != 0)){

    if(dx == 1 || dx == -1 || dy == 1 || dy == -1){
        isItLegit = true;
        return isItLegit;
    }


    if(dx > 0){
        for(int i = actualLocation.col + 1; i < futurelocation.col; i++){
            if((board[actualLocation.row][i] % 10) == 0){              
                isItLegit = true;
            }else{
                isItLegit = false;
                return isItLegit;
            }
        }

    }else if(dx < 0){
        for(int i = futurelocation.col + 1; i < actualLocation.col; i++){
            if((board[actualLocation.row][i] % 10) == 0){                      
                isItLegit = true;
            }else{
                isItLegit = false;
                return isItLegit;
            }
        }
    }

    if(dy > 0){
        for(int j = actualLocation.row + 1; j < futurelocation.row; j++){
            if((board[j][actualLocation.col] % 10) == 0){                         
                isItLegit = true;
            }else{
                isItLegit = false;
                return  isItLegit;
            }
            }
    

        }else if(dy < 0){
        for(int j = actualLocation.row - 1; j > futurelocation.row; j--){
            if((board[j][actualLocation.col] % 10) == 0){                        
                isItLegit = true;
            }else{
                isItLegit = false;
                return isItLegit;
            }
        }
    }
    }

        
        //If its moving like a bishop (same code).

    if(abs(dx) == abs(dy)){

    if(abs(dx) == 1){
        isItLegit = true;
        return isItLegit;
    } 

        if(dx < 0 && dy < 0){
            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row + i][futurelocation.col + i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return isItLegit;
                }
            }

        } else if(dx > 0 && dy < 0){

            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row + i][futurelocation.col - i] == 0){   
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return isItLegit;
                }
            }

        } else if(dx < 0 && dy > 0){

            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row - i][futurelocation.col + i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return isItLegit;
                }
            }

        } else if(dx > 0 && dy > 0){

            for(int i = 1; i < (abs(dx)); i++){
                if(board[futurelocation.row - i][futurelocation.col - i] == 0){
                    isItLegit = true;
                }else{
                    isItLegit = false;
                    return isItLegit;
                }
            }

        }

    }

    }

return isItLegit;
}

bool Board::isPieceValid(int movementCount, T_Coordinates pieceCoords){

    if(board[pieceCoords.row][pieceCoords.col] == 0){
        return false;
    }

    if(movementCount % 2 == 0){
        return board[pieceCoords.row][pieceCoords.col] / 10;
    }else{
        return !(board[pieceCoords.row][pieceCoords.col] / 10);
    }

}

std::vector<T_Coordinates> Board::prohibitedMoves(int movementCount){


    //This function takes the board and the movementCount and generates a list of squares where the king corresponding to the current colour cant go.

    std::vector<T_Coordinates> prohibitedSquares;
    bool isItLegit;

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

                          

                        if(isThreatened(nextMovementCount, actualLocation, futurelocation)){ //... checks if its legit or not...
                            T_Coordinates tempCoord;
                            tempCoord.row = futurelocation.row;
                            tempCoord.col = futurelocation.col;    // ...and the legit ones are saved in an array.
                            prohibitedSquares.push_back(tempCoord);
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
                        
                        if(isThreatened(nextMovementCount, actualLocation, futurelocation)){ //... checks if its legit or not...
                            T_Coordinates tempCoord;
                            tempCoord.row = futurelocation.row;
                            tempCoord.col = futurelocation.col;    // ...and the legit ones are saved in an array.
                            prohibitedSquares.push_back(tempCoord);
                        }

                    }
                }




            } 
        }
    }

    return prohibitedSquares;
}

std::vector<T_Coordinates> Board::legitMoves(int movementCount, T_Coordinates actualLocation){

    std::vector<T_Coordinates> legitMoves;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

        T_Coordinates futureLocation;

        futureLocation.col = i;
        futureLocation.row = j;

        if(isLegit(movementCount, actualLocation, futureLocation)){
            legitMoves.push_back(futureLocation);
        }


        }
    }

return legitMoves;

}

bool Board::isTheKingChecked(int movementCount, std::vector<T_Coordinates> prohibitedSquares){

    //This function checks wether the king is checked or not.

    bool checked = false;

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

    for(int k = 0; k < prohibitedSquares.size(); k++){
        if(prohibitedSquares[k].row == kingrow && prohibitedSquares[k].col == kingcol){
            checked = true;
        }   
    }

return checked;

}

bool Board::isTheKingCheckMated(int movementCount, std::vector<T_Coordinates> prohibitedSquares){

    //This function checks if there exists a legal move such that the king is not in check. It can therefore indicate two different situations:

    // If its executed with the king being in check and it returns "true" in the value matchOver, it means that the king is checkmated, and it means a victory for the opposing player. 
    // If its executed with the king NOT being in check and it returns "true" in the value matchOver, it means a Stalemate, and therefore a draw. 

    bool isItThreatened;
    bool checked;
    std::vector <T_Coordinates> prohibitedSquaresD;
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
                    

                        if(isThreatened(movementCount, actualLocation, futurelocation)){ // ... and checks if its legit or not. If the movement is legit... 
                            board2.updateboard(actualLocation, futurelocation); //... we perform it in a duplicated board... 
                            prohibitedSquaresD =  board2.prohibitedMoves(movementCount); //... we calculate the checked squares in that duplicate board..
                            checked = board2.isTheKingChecked(movementCount, prohibitedSquaresD); //... and we look if the king is still checked.
                             
                            if(checked == false){ //if there is at least one legal move where the king is still not checked, the king is not checkmated.
                                savingMoves = savingMoves + 1;
                                return false;
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

                        if(isThreatened(movementCount, actualLocation, futurelocation)){ // ... and checks if its legit or not. If the movement is legit... 
                            board2.updateboard(actualLocation, futurelocation); //... we perform it in a duplicated board... 
                            prohibitedSquaresD =  board2.prohibitedMoves(movementCount); //... we calculate the checked squares in that duplicate board..
                            checked = board2.isTheKingChecked(movementCount, prohibitedSquaresD); //... and we look if the king is still checked.

                            if(checked == false){ //if there is at least one legal move where the king is still not checked, the king is not checkmated.
                                savingMoves = savingMoves + 1;
                                return false;

                            }
                        }

                        }
                    }
                } 
            }
    }
        
        if(savingMoves == 0){
            return true;
        }

return false;
}

bool Board::isPawnPromoting(int movementCount){

    if(movementCount % 2 == 0){
        return(board[0][0] % 10 == 1|| board[0][1] % 10 == 1 || board[0][2] % 10 == 1 || board[0][3] % 10 == 1 || board[0][4] % 10 == 1 || board[0][5] % 10 == 1 || board[0][6] % 10 == 1 || board[0][7] % 10 == 1);
    }else{
        return(board[7][0] % 10 == 1 || board[7][1] % 10 == 1 || board[7][2] % 10 == 1 || board[7][3] % 10 == 1 || board[7][4] % 10 == 1 || board[7][5] % 10 == 1 || board[7][6] % 10 == 1 || board[7][7] % 10 == 1);
    }

}

void Board::PawnPromotion(int movementCount, SDL_Renderer* renderer){

    T_Coordinates pawnCoords{-1, -1};

    if(movementCount%2==0){
        for(int i = 0; i < 8; i++){
            if(board[0][i]%10==1){
                pawnCoords.row = 0;
                pawnCoords.col = i;
                break;
            }
        }
    }else{
        for(int i = 0; i < 8; i++){
            if(board[7][i]%10==1){
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
            int w = 100; 
            int h = 300;

            importImageInRender(renderer, "assets/images/pawnpromotion.png", x, y, w, h);
            SDL_RenderPresent(renderer);

            std::cout << "PRESENTED" << std::endl;

            SDL_Event e;
            bool promotion = false;
            while (SDL_WaitEvent(&e) && !promotion) {
                if (e.type == SDL_QUIT){
                }else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                    if (e.button.x >= x && e.button.x < x + w && e.button.y >= y && e.button.y < y + h) {
                        switch(e.button.y/75){
                            case 0: 
                                board[pawnCoords.row][pawnCoords.col] = ((board[pawnCoords.row][pawnCoords.col]/10)*10)+3;    // QUEEN
                                promotion = true;
                                break;
                            case 1:
                                board[pawnCoords.row][pawnCoords.col] = ((board[pawnCoords.row][pawnCoords.col]/10)*10)+6;    // KNIGHT
                                promotion = true;
                                break;
                            case 2:
                              board[pawnCoords.row][pawnCoords.col] = ((board[pawnCoords.row][pawnCoords.col]/10)*10)+4;    // ROOK
                              promotion = true;
                                break;
                            case 3:
                                board[pawnCoords.row][pawnCoords.col] = ((board[pawnCoords.row][pawnCoords.col]/10)*10)+5;    // BISHOP
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

            importImageInRender(renderer, "assets/image/pawnpromotion.png", x, y, w, h);
            SDL_RenderPresent(renderer);
            SDL_Event e;
            bool promotion = false;
            while (SDL_WaitEvent(&e) && !promotion) {
                if (e.type == SDL_QUIT){
                }else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                    if (e.button.x >= x && e.button.x < x + w && e.button.y >= y && e.button.y < y + h) {
                        switch(e.button.y/75){
                            case 4: 
                                board[pawnCoords.row][pawnCoords.col] = ((board[pawnCoords.row][pawnCoords.col]/10)*10)+3;    // QUEEN
                                promotion = true;
                                break;
                            case 5:
                                board[pawnCoords.row][pawnCoords.col] = ((board[pawnCoords.row][pawnCoords.col]/10)*10)+6;    // KNIGHT
                                promotion = true;
                                break;
                            case 6:
                                board[pawnCoords.row][pawnCoords.col] = ((board[pawnCoords.row][pawnCoords.col]/10)*10)+4;    // ROOK
                                promotion = true;
                                break;
                            case 7:
                                board[pawnCoords.row][pawnCoords.col] = ((board[pawnCoords.row][pawnCoords.col]/10)*10)+5;    // BISHOP
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

bool Board::haveSameColor(T_Coordinates actualLocation, T_Coordinates futurelocation){

    return ( !(board[futurelocation.row][futurelocation.col] == 0) && (board[actualLocation.row][actualLocation.col] / 10) == (board[futurelocation.row][futurelocation.col] / 10));

}