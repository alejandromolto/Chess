#include "GameScene.h"
#include "board.h"
#include "utils.h"
#include <algorithm>
#include <vector>
#include <iostream>

void BScene::printBoard()
{
    // Board decoration.
    importImageInRender(renderer, "assets/images/playingBackground.png", 0, 0, width, height);

    // Chess board.
    board.printboard((width * 600) / 1152, (height * 600) / 680, renderer);

    // Strips (A-H) and (1-8)
    importImageInRender(renderer, "assets/images/letterBar.png", 0, (height * 600) / 680, (width * 600) / 1152, (height * 80) / 680);
    importImageInRender(renderer, "assets/images/numberBar.png", (width * 600) / 1152, 0, (width * 80) / 1152, (height * 600) / 680);

    // Forfeit button
    importImageInRender(renderer, "assets/images/surrendButton.png", (width * 527) / 864, (height * 364) / 510, (width * 328) / 864, (height * 141) / 510);

    // Exit button
    importImageInRender(renderer, "assets/images/back.png", width - width / 50 - width / 12, height / 50, width / 12, width / 12);

    SDL_RenderPresent(renderer);
}

void BScene::printBoardAndLegitMoves(T_Coordinates pieceCoords, int movementCount)
{
    // Board decoration.
    importImageInRender(renderer, "assets/images/playingBackground.png", 0, 0, width, height);

    // Chess board.
    board.printboard((width * 600) / 1152, (height * 600) / 680, renderer);

    // Strips (A-H) and (1-8)
    importImageInRender(renderer, "assets/images/letterBar.png", 0, (height * 600) / 680, (width * 600) / 1152, (height * 80) / 680);
    importImageInRender(renderer, "assets/images/numberBar.png", (width * 600) / 1152, 0, (width * 80) / 1152, (height * 600) / 680);

    // Forfeit button
    importImageInRender(renderer, "assets/images/surrendButton.png", (width * 527) / 864, (height * 364) / 510, (width * 328) / 864, (height * 141) / 510);

    // Exit button
    importImageInRender(renderer, "assets/images/back.png", width - width / 50 - width / 12, height / 50, width / 12, width / 12);

    int squareW = (width * 600) / 1152 / 8;
    int squareH = (height * 600) / 680 / 8;

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
                rect.y = i * squareH;
                rect.x = j * squareW;
                rect.w = squareW;
                rect.h = squareH;

                SDL_SetRenderDrawColor(renderer, 24, 87, 110, 125);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    // Castling
    if (board.getboard()[pieceCoords.row][pieceCoords.col] % 10 == 2)
    {
        if (movementCount % 2 == 0 && pieceCoords.row == 7 && pieceCoords.col == 4)
        {

            T_Coordinates tempCoord1Long = {245713, 1046};
            T_Coordinates tempCoord1Short = {245713, 54027};
            T_Coordinates tempCoord2 = {10, 10};

            if (board.isLegit(tempCoord1Long, tempCoord2))
            { // White long
                SDL_Rect rect;
                SDL_SetRenderDrawColor(renderer, 27, 79, 10, 100);
                rect.y = 7 * squareH;
                rect.x = 2 * squareW;
                rect.w = squareW;
                rect.h = squareH;
                SDL_RenderFillRect(renderer, &rect);
            }
            if (board.isLegit(tempCoord1Short, tempCoord2))
            { // White short
                SDL_Rect rect;
                SDL_SetRenderDrawColor(renderer, 27, 79, 10, 100);
                rect.y = 7 * squareH;
                rect.x = 6 * squareW;
                rect.w = squareW;
                rect.h = squareH;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
        else if (movementCount % 2 != 0 && pieceCoords.row == 0 && pieceCoords.col == 4)
        {
            T_Coordinates tempCoord1Long = {245713, 1046};
            T_Coordinates tempCoord1Short = {245713, 54027};
            T_Coordinates tempCoord2 = {-10, -10};

            if (board.isLegit(tempCoord1Long, tempCoord2))
            { // Black long
                SDL_Rect rect;
                SDL_SetRenderDrawColor(renderer, 27, 79, 10, 100);
                rect.y = 0;
                rect.x = 2 * squareW;
                rect.w = squareW;
                rect.h = squareH;
                SDL_RenderFillRect(renderer, &rect);
            }
            if (board.isLegit(tempCoord1Short, tempCoord2))
            { // Black short
                SDL_Rect rect;
                SDL_SetRenderDrawColor(renderer, 27, 79, 10, 100);
                rect.y = 0;
                rect.x = 6 * squareW;
                rect.w = squareW;
                rect.h = squareH;
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}
