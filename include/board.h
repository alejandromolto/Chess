#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <set>

struct T_Coordinates{ 
    int row;
    int col; 

    bool operator==(const T_Coordinates& other) const {
        return row == other.row && col == other.col;
    }
    
};

class Board{
    private:
        int board[8][8];
        bool matchOver;
        int movementCount = 0;
        bool whiteCanCastleLong = true;
        bool whiteCanCastleShort = true;
        bool blackCanCastleLong = true;
        bool blackCanCastleShort = true;
        T_Coordinates enPassantTarget;
        std::vector<std::vector<int>> history;
    public:
        Board();
        Board(int board[8][8], int movementCount);
        int (*getboard())[8] { return board; }
        int getMovementCount(){ return movementCount; }
        void setMovementCount(int movementCount);
        void setboard(int board[8][8]);
        void printboard(int width, int height, SDL_Renderer *renderer, SDL_Window *window);   
        void updateboard(T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isThreatened(T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isLegal(T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isTheKingCheckMated(std::vector<T_Coordinates> prohibitedSquares);
        bool isPieceValid(T_Coordinates pieceCoords);
        std::vector<T_Coordinates> prohibitedMoves();
        std::vector<T_Coordinates> legitMoves(T_Coordinates actualLocation);
        std::set<T_Coordinates> controlledSquares();
        bool isTheKingChecked(std::vector<T_Coordinates> prohibitedSquares);
        bool isPawnPromoting();
        void PawnPromotion(SDL_Renderer* renderer);
        void AIPawnPromotion();
        bool haveSameColor(T_Coordinates actualLocation, T_Coordinates futurelocation);
        int evaluate();
        std::vector<std::pair<T_Coordinates,T_Coordinates>> generateAllLegalMoves();
        std::pair<T_Coordinates, T_Coordinates> bestMove(std::vector<std::pair<T_Coordinates,T_Coordinates>> allLegalMoves);
        std::vector<int> flattenBoardAndAppend();
        void exportGametoFile(std::string filename);
        void importGametoBoard(std::string filename, int numgame);

};

#endif