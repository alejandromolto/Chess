#include "include/utils.h"
#include "include/board.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <SDL2/SDL.h>
#include "piece.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "king.h"
#include "queen.h"
#include "rook.h"

Board::Board()
{

    int chessBoard[8][8] = {
        {4, 6, 5, 3, 2, 5, 6, 4},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {11, 11, 11, 11, 11, 11, 11, 11},
        {14, 16, 15, 13, 12, 15, 16, 14}};

    setboard(chessBoard);

    movementCount = 0;
}

Board::Board(int board[8][8], int movementCount)
{
    setboard(board);
    this->movementCount = movementCount;
}

Board::Board(const Board& other)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = other.board[i][j];
        }
    }

    movementCount = other.movementCount;
    whiteCanCastleLong = other.whiteCanCastleLong;
    whiteCanCastleShort = other.whiteCanCastleShort;
    blackCanCastleLong = other.blackCanCastleLong;
    blackCanCastleShort = other.blackCanCastleShort;
    enPassantTarget = other.enPassantTarget;
    history = other.history;
}

void Board::setboard(int board[8][8])
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->board[i][j] = board[i][j];
        }
    }
}

void Board::setMovementCount(int movementCount)
{
    this->movementCount = movementCount;
}

void Board::turnOver(){
    this->movementCount++;
}

void Board::printboard(int width, int height, SDL_Renderer *renderer)
{

    SDL_Rect rect;
    int blockwidth = width / 8;
    int blockheight = height / 8;

    // This function displays the current state of the board.

    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            if ((i + j) % 2 == 0)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // blanco
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 56, 52, 52, 255); // negro
            }

            rect.x = i * blockwidth;
            rect.y = j * blockheight;
            rect.w = blockwidth;
            rect.h = blockheight;
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            switch (board[i][j] % 10)
            {
            case 0:
                // Casilla vacía
                break;
            case 1:
                // Peón
                if ((board[i][j]) / 10 != 0)
                {
                    importImageInRender(renderer, "assets/images/whitepawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                else
                {
                    importImageInRender(renderer, "assets/images/blackpawn.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                break;
            case 2:
                // Rey
                if ((board[i][j]) / 10 != 0)
                {
                    importImageInRender(renderer, "assets/images/whiteking.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                else
                {
                    importImageInRender(renderer, "assets/images/blackking.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                break;
            case 3:
                // Reina
                if ((board[i][j]) / 10 != 0)
                {
                    importImageInRender(renderer, "assets/images/whitequeen.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                else
                {
                    importImageInRender(renderer, "assets/images/blackqueen.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                break;
            case 4:
                // Torre
                if ((board[i][j]) / 10 != 0)
                {
                    importImageInRender(renderer, "assets/images/whiterook.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                else
                {
                    importImageInRender(renderer, "assets/images/blackrook.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                break;
            case 5:
                // Alfil
                if ((board[i][j]) / 10 != 0)
                {
                    importImageInRender(renderer, "assets/images/whitebishop.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                else
                {
                    importImageInRender(renderer, "assets/images/blackbishop.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                break;
            case 6:
                // Caballo
                if ((board[i][j]) / 10 != 0)
                {
                    importImageInRender(renderer, "assets/images/whiteknight.png", j * blockwidth, i * blockheight, blockwidth, blockheight);
                }
                else
                {
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

void Board::updateboard(T_Coordinates actualLocation, T_Coordinates futureLocation)
{

    // This function modifies the board state based on the player's move. This function does not verify that the movement is Legal, it just performs it.

    int square = 0;

    if (actualLocation.row > 0 && actualLocation.row < 8 && actualLocation.col > 0 && actualLocation.col < 8)
    {
        square = board[actualLocation.row][actualLocation.col];
    }

    if (movementCount == 0)
    {
        flattenBoardAndAppend();
    }

    if (actualLocation.row != 245713)
    { // Standard move.

        switch (board[actualLocation.row][actualLocation.col] % 10)
        {       // Castling purposes (Some moves disable the possibility to castle)
        case 2: // KING
            if (board[actualLocation.row][actualLocation.col] / 10 == 1)
            {
                whiteCanCastleLong = false;
                whiteCanCastleShort = false;
            }
            else
            {
                blackCanCastleLong = false;
                blackCanCastleShort = false;
            }
            break;
        case 4: // ROOK
            if (board[actualLocation.row][actualLocation.col] / 10 == 1)
            {
                if (actualLocation.col == 1)
                {
                    whiteCanCastleLong = false;
                }
                else if (actualLocation.col == 7)
                {
                    whiteCanCastleShort = false;
                }
            }
            else
            {
                if (actualLocation.col == 1)
                {
                    blackCanCastleLong = false;
                }
                else if (actualLocation.col == 7)
                {
                    blackCanCastleShort = false;
                }
            }
            break;
        default:
            break;
        }

        board[futureLocation.row][futureLocation.col] = board[actualLocation.row][actualLocation.col]; // Standard move.
        board[actualLocation.row][actualLocation.col] = 0;

        if (board[futureLocation.row][futureLocation.col] % 10 == 1 && abs(actualLocation.row - futureLocation.row) == 2)
        { // Pawn moving two squares at once (Enabling en passant).
            if (movementCount % 2 == 0)
            {
                enPassantTarget.row = futureLocation.row + 1;
                enPassantTarget.col = futureLocation.col;
            }
            else
            {
                enPassantTarget.row = futureLocation.row - 1;
                enPassantTarget.col = futureLocation.col;
            }
        }
        else if (enPassantTarget.row == futureLocation.row && enPassantTarget.col == futureLocation.col && square % 10 == 1)
        { // En passant.

            if (movementCount % 2 == 0)
            {
                board[enPassantTarget.row + 1][enPassantTarget.col] = 0;
            }
            else
            {
                board[enPassantTarget.row - 1][enPassantTarget.col] = 0;
            }

            enPassantTarget = {-1, -1};
        }
        else
        {
            enPassantTarget = {-1, -1};
        }
    }
    else
    { // Castling.

        if (actualLocation.col == 1046)
        { // Queenside (long) castle
            if (futureLocation.row == 10 && futureLocation.col == 10)
            {                              // White
                board[7][2] = board[7][4]; // King e1 -> c1
                board[7][4] = 0;

                board[7][3] = board[7][0]; // Rook a1 -> d1
                board[7][0] = 0;
            }
            else if (futureLocation.row == -10 && futureLocation.col == -10)
            {                              // Black
                board[0][2] = board[0][4]; // King e8 -> c8
                board[0][4] = 0;

                board[0][3] = board[0][0]; // Rook a8 -> d8
                board[0][0] = 0;
            }
        }
        else if (actualLocation.col == 54027)
        { // Kingside (short) castle
            if (futureLocation.row == 10 && futureLocation.col == 10)
            {                              // White
                board[7][6] = board[7][4]; // King e1 -> g1
                board[7][4] = 0;

                board[7][5] = board[7][7]; // Rook h1 -> f1
                board[7][7] = 0;
            }
            else if (futureLocation.row == -10 && futureLocation.col == -10)
            {                              // Black
                board[0][6] = board[0][4]; // King e8 -> g8
                board[0][4] = 0;

                board[0][5] = board[0][7]; // Rook h8 -> f8
                board[0][7] = 0;
            }
        }
    }

    flattenBoardAndAppend();
}

bool Board::isThreatened(T_Coordinates actualLocation, T_Coordinates futureLocation)
{

    bool isItThreatened = false;

    // This function checks if a square of the board is threteaned by a piece, by taking as input a particular movement (with the actual location and the future location)
    // and returns the condition isItThreatened with wether or not the square can be considered threatened.

    // If the piece is not a pawn, then the condition "threatened" is equal to the condition "legit",thus if the piece is not a pawn, then isItThreatened is equal to isItLegit:

    if (board[actualLocation.row][actualLocation.col] % 10 == 2 ||
        board[actualLocation.row][actualLocation.col] % 10 == 3 ||
        board[actualLocation.row][actualLocation.col] % 10 == 4 ||
        board[actualLocation.row][actualLocation.col] % 10 == 5 ||
        board[actualLocation.row][actualLocation.col] % 10 == 6)
    {

        isItThreatened = isLegit(actualLocation, futureLocation);
    }

    // Now, if the piece is a pawn, some special rules need to be added.

    // GENERAL CHECK for pawns:

    if (actualLocation.col > 7 || actualLocation.col < 0 || actualLocation.row > 7 || actualLocation.row < 0)
    {
        return false;
    }

    if (futureLocation.col > 7 || futureLocation.col < 0 || futureLocation.row > 7 || futureLocation.row < 0)
    {
        return false;
    }

    if (actualLocation.col == futureLocation.col && actualLocation.row == futureLocation.row)
    {
        return false;
    }

    if ((board[actualLocation.row][actualLocation.col] % 10) == 0)
    {
        return false;
    }

    if ((movementCount % 2 == 0 && (board[actualLocation.row][actualLocation.col] / 10) == 0) ||
        (movementCount % 2 != 0 && (board[actualLocation.row][actualLocation.col] / 10) == 1))
    {
        return false;
    }

    if ((movementCount % 2 == 0 && board[futureLocation.row][futureLocation.col] / 10 == 1) ||
        (movementCount % 2 != 0 && board[futureLocation.row][futureLocation.col] / 10 == 0 &&
         board[futureLocation.row][futureLocation.col] % 10 != 0))
    {
        return false;
    }

    // SPECIAL RULES.
    // The position is threatened by a pawn only if its diagonal

    int dx = futureLocation.col - actualLocation.col;
    int dy = futureLocation.row - actualLocation.row;

    if (board[actualLocation.row][actualLocation.col] % 10 == 1)
    {
        // White pawns
        if (board[actualLocation.row][actualLocation.col] / 10 == 1)
        {
            if ((dx == 1 || dx == -1) && dy == -1)
            {
                isItThreatened = true;
            }

            // Black pawns
        }
        else
        {
            if ((dx == 1 || dx == -1) && dy == 1)
            {
                isItThreatened = true;
            }
        }
    }

    return isItThreatened;
}

bool Board::isLegal(T_Coordinates actualLocation, T_Coordinates futureLocation)
{

    // This function checks whether the move is legal or not, that is, checks if its legit and then checks if it leaves the king on check.


    bool isLegalVar = isLegit(actualLocation, futureLocation);

    if (!isLegalVar)
    {
        return false;
    }
    else
    {
        Board duplicateBoard(board, getMovementCount());
        duplicateBoard.updateboard(actualLocation, futureLocation);

        if (duplicateBoard.isTheKingChecked(duplicateBoard.prohibitedMoves()))
        {
            isLegalVar = false;
        }
        else
        {
            isLegalVar = true;
        }
    }

    return isLegalVar;
}

bool Board::isLegit(T_Coordinates actualLocation, T_Coordinates futureLocation)
{

    // This function checks whether the move is legitimate or not.

    bool isItLegit = false;
    Piece* p = nullptr;

    if (actualLocation.row == 245713){
        p = new Piece(this);
    }else{
        switch (board[actualLocation.row][actualLocation.col] % 10) {
            case 1: p = new Pawn(this); break;
            case 2: p = new King(this); break;
            case 3: p = new Queen(this); break;
            case 4: p = new Rook(this); break;
            case 5: p = new Bishop(this); break;
            case 6: p = new Knight(this); break;
            default: return false;
        }
    }

    isItLegit = p->isLegit(actualLocation, futureLocation);
    delete p;
    return isItLegit;
}

bool Board::isPieceValid(T_Coordinates pieceCoords)
{

    if (board[pieceCoords.row][pieceCoords.col] == 0)
    {
        return false;
    }

    if (movementCount % 2 == 0)
    {
        return board[pieceCoords.row][pieceCoords.col] / 10;
    }
    else
    {
        return !(board[pieceCoords.row][pieceCoords.col] / 10);
    }
}

std::vector<T_Coordinates> Board::prohibitedMoves()
{

    // This function takes the board and the movementCount and generates a list of squares where the king corresponding to the current colour cant go.

    std::vector<T_Coordinates> prohibitedSquares;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (movementCount % 2 != 0 && board[i][j] / 10 == 1 && board[i][j] % 10 != 0)
            { // black's moving & the piece is white...

                for (int k = 0; k < 8; k++)
                {
                    for (int t = 0; t < 8; t++)
                    { //... the program checks every possible move for that piece...

                        T_Coordinates actualLocation;
                        actualLocation.row = i;
                        actualLocation.col = j;

                        T_Coordinates futureLocation;
                        futureLocation.row = k;
                        futureLocation.col = t;

                        setMovementCount(getMovementCount() + 1);

                        if (isThreatened(actualLocation, futureLocation))
                        { //... checks if its legit or not...
                            T_Coordinates tempCoord;
                            tempCoord.row = futureLocation.row;
                            tempCoord.col = futureLocation.col; // ...and the legit ones are saved in an array.
                            prohibitedSquares.push_back(tempCoord);
                        }

                        setMovementCount(getMovementCount() - 1);
                    }
                }
            }
            else if (movementCount % 2 == 0 && board[i][j] / 10 == 0 && board[i][j] % 10 != 0)
            { // white's moving & the piece is black

                for (int k = 0; k < 8; k++)
                {
                    for (int t = 0; t < 8; t++)
                    { //... the program checks every possible move for that piece...

                        T_Coordinates actualLocation;
                        actualLocation.row = i;
                        actualLocation.col = j;

                        T_Coordinates futureLocation;
                        futureLocation.row = k;
                        futureLocation.col = t;

                        setMovementCount(getMovementCount() + 1);

                        if (isThreatened(actualLocation, futureLocation))
                        { //... checks if its legit or not...
                            T_Coordinates tempCoord;
                            tempCoord.row = futureLocation.row;
                            tempCoord.col = futureLocation.col; // ...and the legit ones are saved in an array.
                            prohibitedSquares.push_back(tempCoord);
                        }

                        setMovementCount(getMovementCount() - 1);
                    }
                }
            }
        }
    }

    return prohibitedSquares;
}

std::vector<T_Coordinates> Board::legitMoves(T_Coordinates actualLocation)
{

    // This functon can be used when the legit moves that are bothe legal and not legal (Moves that leave the king on check) must be visualized.

    std::vector<T_Coordinates> legitMoves;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            T_Coordinates futureLocation;

            futureLocation.col = i;
            futureLocation.row = j;

            if (isLegit(actualLocation, futureLocation))
            {
                legitMoves.push_back(futureLocation);
            }
        }
    }

    return legitMoves;
}

bool Board::isTheKingChecked(std::vector<T_Coordinates> prohibitedSquares)
{

    // This function checks wether the king is checked or not.

    bool checked = false;

    int kingrow;
    int kingcol;

    // We locate the king of the corresponding color

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] % 10 == 2 && ((board[i][j] / 10 == 0 && movementCount % 2 != 0) ||
                                          (board[i][j] / 10 == 1 && movementCount % 2 == 0)))
            {

                kingrow = i;
                kingcol = j;
            }
        }
    }

    // Then check if the king is in any of the checked positions.

    for (int k = 0; k < static_cast<int>(prohibitedSquares.size()); k++)
    {
        if (prohibitedSquares[k].row == kingrow && prohibitedSquares[k].col == kingcol)
        {
            checked = true;
        }
    }

    return checked;
}

bool Board::isTheKingCheckMated()
{

    // This function checks if there exists a legal move such that the king is not in check. It can therefore indicate two different situations:

    // If its executed with the king being in check and it returns "true" in the value matchOver, it means that the king is checkmated, and it means a victory for the opposing player.
    // If its executed with the king NOT being in check and it returns "true" in the value matchOver, it means a Stalemate, and therefore a draw.

    bool checked;
    std::vector<T_Coordinates> prohibitedSquaresD;
    int savingMoves = 0;

    // The function must check if there is any legal move that can save the king ¿How?.
    // Well using the function isTheKingChecked and prohibitedMoves we can calculate if there is any legal move that makes the king NOT checked in the next move.

    // To do that, we duplicate the chess board for trials (to try every possible move)

    Board board2 = Board(board, movementCount);

    // Then the magic comes. We check every piece.

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (movementCount % 2 == 0 && board[i][j] / 10 == 1 && board[i][j] % 10 != 0)
            { // If white is moving & the piece is white (which means that white is checked)...

                for (int k = 0; k < 8; k++)
                {
                    for (int t = 0; t < 8; t++)
                    { //... the program checks every possible move for that piece...

                        board2.setboard(board);

                        T_Coordinates actualLocation;
                        actualLocation.row = i;
                        actualLocation.col = j;
                        T_Coordinates futureLocation;
                        futureLocation.row = k;
                        futureLocation.col = t;

                        if (isThreatened(actualLocation, futureLocation))
                        {                                                          // ... and checks if its legit or not. If the movement is legit...
                            board2.updateboard(actualLocation, futureLocation);    //... we perform it in a duplicated board...
                            prohibitedSquaresD = board2.prohibitedMoves();         //... we calculate the checked squares in that duplicate board..
                            checked = board2.isTheKingChecked(prohibitedSquaresD); //... and we look if the king is still checked.

                            if (checked == false)
                            { // if there is at least one legal move where the king is still not checked, the king is not checkmated.
                                savingMoves = savingMoves + 1;
                                return false;
                            }
                        }
                    }
                }
            }
            else if (movementCount % 2 != 0 && board[i][j] / 10 == 0 && board[i][j] % 10 != 0)
            { // If black is moving & the piece is black (which means that black is checked)...

                for (int k = 0; k < 8; k++)
                {
                    for (int t = 0; t < 8; t++)
                    { //... the program checks every possible move for that piece...

                        T_Coordinates actualLocation;
                        actualLocation.row = i;
                        actualLocation.col = j;
                        T_Coordinates futureLocation;
                        futureLocation.row = k;
                        futureLocation.col = t;

                        board2.setboard(board);

                        if (isThreatened(actualLocation, futureLocation))
                        {                                                          // ... and checks if its legit or not. If the movement is legit...
                            board2.updateboard(actualLocation, futureLocation);    //... we perform it in a duplicated board...
                            prohibitedSquaresD = board2.prohibitedMoves();         //... we calculate the checked squares in that duplicate board..
                            checked = board2.isTheKingChecked(prohibitedSquaresD); //... and we look if the king is still checked.

                            if (checked == false)
                            { // if there is at least one legal move where the king is still not checked, the king is not checkmated.
                                savingMoves = savingMoves + 1;
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    if (savingMoves == 0)
    {
        return true;
    }

    return false;
}

bool Board::isPawnPromoting()
{

    if (movementCount % 2 == 0)
    {
        return (board[0][0] % 10 == 1 || board[0][1] % 10 == 1 || board[0][2] % 10 == 1 || board[0][3] % 10 == 1 || board[0][4] % 10 == 1 || board[0][5] % 10 == 1 || board[0][6] % 10 == 1 || board[0][7] % 10 == 1);
    }
    else
    {
        return (board[7][0] % 10 == 1 || board[7][1] % 10 == 1 || board[7][2] % 10 == 1 || board[7][3] % 10 == 1 || board[7][4] % 10 == 1 || board[7][5] % 10 == 1 || board[7][6] % 10 == 1 || board[7][7] % 10 == 1);
    }
}

bool Board::isPawnPromoting(bool nexTurn)
{
    if(nexTurn){
        movementCount--;
    }

    if (movementCount % 2 == 0)
    {
        return (board[0][0] % 10 == 1 || board[0][1] % 10 == 1 || board[0][2] % 10 == 1 || board[0][3] % 10 == 1 || board[0][4] % 10 == 1 || board[0][5] % 10 == 1 || board[0][6] % 10 == 1 || board[0][7] % 10 == 1);
    }
    else
    {
        return (board[7][0] % 10 == 1 || board[7][1] % 10 == 1 || board[7][2] % 10 == 1 || board[7][3] % 10 == 1 || board[7][4] % 10 == 1 || board[7][5] % 10 == 1 || board[7][6] % 10 == 1 || board[7][7] % 10 == 1);
    }
}

void Board::PawnPromotion(T_Coordinates pawnCoords, int NewValue)
{
    board[pawnCoords.row][pawnCoords.col] = NewValue;
}

bool Board::haveSameColor(T_Coordinates actualLocation, T_Coordinates futureLocation)
{
    return (!(board[futureLocation.row][futureLocation.col] == 0) && (board[actualLocation.row][actualLocation.col] / 10) == (board[futureLocation.row][futureLocation.col] / 10));
}

std::vector<int> Board::flattenBoardAndAppend()
{

    std::vector<int> flatBoard;
    flatBoard.reserve(64); // This reserves capacity for 64 integers. (8x8 board)

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            flatBoard.push_back(board[i][j]);
        }
    }

    history.push_back(flatBoard);
    return flatBoard;
}

std::vector<std::pair<T_Coordinates, T_Coordinates>> Board::generateAllLegalMoves()
{

    std::vector<std::pair<T_Coordinates, T_Coordinates>> legalMoves;

    // Generate all natural moves that are legal (One piece moves from point A to point B, En-passant included)

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                for (int l = 0; l < 8; l++)
                {

                    T_Coordinates actualCoord = {i, j};
                    T_Coordinates futureCoord = {k, l};

                    if (isLegal(actualCoord, futureCoord))
                    {
                        legalMoves.emplace_back(std::make_pair(actualCoord, futureCoord));
                    }
                }
            }
        }
    }

    // Add castling moves.
    T_Coordinates longCastle = {245713, 1046};
    T_Coordinates shortCastle = {245713, 54027};
    T_Coordinates white = {10, 10};
    T_Coordinates black = {-10, -10};

    if (isLegal(longCastle, white))
    { // white long
        legalMoves.emplace_back(std::make_pair(longCastle, white));
    }
    if (isLegal(longCastle, black))
    { // black long
        legalMoves.emplace_back(std::make_pair(longCastle, black));
    }
    if (isLegal(shortCastle, white))
    { // white short
        legalMoves.emplace_back(std::make_pair(shortCastle, white));
    }
    if (isLegal(shortCastle, black))
    { // black short
        legalMoves.emplace_back(std::make_pair(shortCastle, black));
    }

    // Return the vector with all the legal moves.
    return legalMoves;
}
