#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <set>
#include "piece.h"



class Board{
    private:
        // Main attributes 
        int board[8][8];
        int movementCount = 0;

        // Castling-Related attributes    
        bool whiteCanCastleLong = true;
        bool whiteCanCastleShort = true;
        bool blackCanCastleLong = true;
        bool blackCanCastleShort = true;
    
        // En-Passant related attributes   
        T_Coordinates enPassantTarget;
    
        // Import/Export related attributes   
        std::vector<std::vector<int>> history;
    
        // AI related methods/attributes
        int maxi(int depth, int alpha, int beta );
        int mini(int depth, int alpha, int beta);
    
    public:

        // Constructors
        Board();
        Board(int board[8][8], int movementCount);
        Board(const Board& otherBoard);

        // Getters/Setters 
        int (*getboard())[8] { return board; }
        std::vector<std::vector<int>> gethistory(){ return history; }
        int getMovementCount(){ return movementCount; }
        bool isWhiteTurn(){ return movementCount%2==0; }
        void setMovementCount(int movementCount);
        void setboard(int board[8][8]);
        void turnOver();
        bool getWhiteCanCastleLong(){ return whiteCanCastleLong; }
        bool getWhiteCanCastleShort(){ return whiteCanCastleShort; }
        bool getBlackCanCastleLong(){ return blackCanCastleLong; }
        bool getBlackCanCastleShort(){ return blackCanCastleShort; }
        T_Coordinates getEnPassantTarget(){return enPassantTarget; }

        // Functionalities
        void printboard(int width, int height, SDL_Renderer *renderer);   
        void updateboard(T_Coordinates actualLocation, T_Coordinates futurelocation);
        void PawnPromotion(T_Coordinates pawnCoords, int NewValue, bool isWhite);
        T_Coordinates getLocationOfPawnPromoting();

        // Simple checks
        bool isThreatened(T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isLegit(T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isLegal(T_Coordinates actualLocation, T_Coordinates futurelocation);

        // Vector/Set generators using simple checks.
        std::vector<T_Coordinates> prohibitedMoves(); 
        std::vector<T_Coordinates> legitMoves(T_Coordinates actualLocation);
        std::set<T_Coordinates> controlledSquares();
        std::vector<std::pair<T_Coordinates,T_Coordinates>> generateAllLegalMoves();

        // Checks using those vectors/sets.
        bool isTheKingCheckMated();
        bool isTheKingChecked(std::vector<T_Coordinates> prohibitedSquares);

        // Import/Export
        std::vector<int> flattenBoardAndAppend();
        void exportGametoFile(std::string filename);
        bool importGametoBoard(std::string filename, int numgame);

        // AI
        void AIPawnPromotion();
        int evaluate();
        std::pair<T_Coordinates, T_Coordinates> bestMoveWithMinimax(int depth, int alpha, int beta);

        // Other
        bool haveSameColor(T_Coordinates actualLocation, T_Coordinates futurelocation);
        bool isPieceValid(T_Coordinates pieceCoords);
        bool isPawnPromoting();
        bool isPawnPromoting(bool nexTurn);


};

#endif