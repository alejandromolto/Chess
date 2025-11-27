#include "Scene.h"
#include <iostream>
#include "MainMenuScene.h"
#include "OptionsMenuScene.h"
#include "ChooseMatchScene.h"
#include "utils.h"
#include "TwoPlayerScene.h"
#include "ForfeitScene.h"
#include "ExitScene.h"
#include "PawnPromotionScene.h"
#include "EndGameScene.h"

bool TwoPlayerScene::render()
{

    bool input = true;

    std::vector<T_Coordinates> prohibitedSquares = board.prohibitedMoves();
    if (board.isTheKingCheckMated())
    {
        input = false;
    }
    if (phase == 1)
    {
        printBoard();
    }
    else if (phase == 2)
    {
        printBoardAndLegitMoves(firstPieceCoords, board.getMovementCount());
    }

    return input;
}

Scene *TwoPlayerScene::HandleEvent(SDL_Point click)
{

    std::vector<T_Coordinates> prohibitedSquares = board.prohibitedMoves();
    if (board.isTheKingCheckMated())
    {
        if (board.isTheKingChecked(prohibitedSquares))
        {
            if (board.isWhiteTurn())
            {
                return new EndGameScene(this, renderer, width, height, filename, false, true);
            }
            else
            {
                return new EndGameScene(this, renderer, width, height, filename, true, false);
            }
        }
        else
        {
            return new EndGameScene(this, renderer, width, height, filename, false, false);
         }
    }

    int mx = click.x;
    int my = click.y;

    if(mx == -1 && my == -1){
        return nullptr;
    }

    int squareW = width * 600 / 1152 / 8;
    int squareH = height * 600 / 680 / 8;

    if (phase == 1) // SELECTING PIECE
    {
        if (mx / squareW >= 0 && mx / squareW < 8 && my / squareH >= 0 && my / squareH < 8)
        { // Standard case.
            firstPieceCoords.col = mx / squareW;
            firstPieceCoords.row = my / squareH;
            if(board.isPieceValid(firstPieceCoords)){
                nextPhase();
            }
            return this;
        }
        else if (mx >= (width * 527) / 864 && mx < (width * 527) / 864 + (width * 328) / 864 && my >= (height * 364) / 510 && my < (height * 364) / 510 + (height * 141) / 510)
        { // Forfeit button
            return new ForfeitScene(this, renderer, width, height, filename, "assets/images/forfeit.png");
        }
        else if (mx > width - width / 50 - width / 12 && mx < width - width / 50 - width / 12 + width / 12 && my > height / 50 && my < height / 50 + width / 12)
        { // Normal exit
            return new ExitScene(this, renderer, width, height, filename, "assets/images/matchEnd.png");
        }
        else
        {
            return this;
        }
    }
    else if (phase == 2) // PERFORMING MOVE
    {

        bool kingClicked = board.getboard()[firstPieceCoords.row][firstPieceCoords.col] % 10 == 2;
        bool castling = false;

        if (kingClicked) // CASTLING
        {
            T_Coordinates longCastle = {245713, 1046};
            T_Coordinates shortCastle = {245713, 54027};
            T_Coordinates white = {10, 10};
            T_Coordinates black = {-10, -10};

            if (board.isLegit(longCastle, white))
            { // white long
                if (mx / squareW >= 2 && mx / squareW < 3 && my / squareH >= 7 && my / squareH < 8)
                {
                    firstPieceCoords = longCastle;
                    secondPieceCoords = white;
                    castling = true;
                }
            }
            if (board.isLegit(longCastle, black))
            { // black long
                if (mx / squareW >= 2 && mx / squareW < 3 && my / squareH >= 0 && my / squareH < 1)
                {
                    firstPieceCoords = longCastle;
                    secondPieceCoords = black;
                    castling = true;
                }
            }
            if (board.isLegit(shortCastle, white))
            { // white short
                if (mx / squareW >= 6 && mx / squareW < 7 && my / squareH >= 7 && my / squareH < 8)
                {
                    firstPieceCoords = shortCastle;
                    secondPieceCoords = white;
                    castling = true;
                }
            }
            if (board.isLegit(shortCastle, black))
            { // black short
                if (mx / squareW >= 6 && mx / squareW < 7 && my / squareH >= 0 && my / squareH < 1)
                {
                    firstPieceCoords = shortCastle;
                    secondPieceCoords = black;
                    castling = true;
                }
            }
        }
        // REGULAR MOVES

        if(!castling){
            if (mx / squareW >= 0 && mx / squareW < 8 && my / squareH >= 0 && my / squareH < 8)
            { // Standard case.
                secondPieceCoords.col = mx / squareW;
                secondPieceCoords.row = my / squareH;
                if (board.haveSameColor(firstPieceCoords, secondPieceCoords))
                {
                    firstPieceCoords = secondPieceCoords;
                    return this;
                }
            }
            else if (mx >= (width * 527) / 864 && mx < (width * 527) / 864 + (width * 328) / 864 && my >= (height * 364) / 510 && my < (height * 364) / 510 + (height * 141) / 510)
            { // Forfeit button
                // IF USER CONFIRMS
                return new ForfeitScene(this, renderer, width, height, filename, "assets/images/forfeit.png");
            }
            else if (mx > width - width / 50 - width / 12 && mx < width - width / 50 - width / 12 + width / 12 && my > height / 50 && my < height / 50 + width / 12)
            { // Normal exit
                // IF USER CONIRMS
                return new ExitScene(this, renderer, width, height, filename, "assets/images/matchEnd.png");
            }
            else
            {
                setPhase(1);
                return this;
            }
        }
 

        if(board.isLegal(firstPieceCoords, secondPieceCoords)){
            board.updateboard(firstPieceCoords, secondPieceCoords);
            setPhase(1);
            if(board.isPawnPromoting()){
                T_Coordinates pawnPromoting = board.getLocationOfPawnPromoting();
                return new PawnPromotionScene(this, renderer, width, height, filename, &board, pawnPromoting); 
            }else{
                board.turnOver();
            }
            return this;
        }else{
            setPhase(1);
            return this;
        }
    }else{ // ERROR
        return nullptr;
    }

}
