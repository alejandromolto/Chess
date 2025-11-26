#include <iostream>
#include "utils.h"
#include "BScene.h"
#include "PawnPromotionScene.h"

PawnPromotionScene::PawnPromotionScene(Scene *lastScene, SDL_Renderer *renderer, int width, int height, std::string filename, Board *board, T_Coordinates pawnPromoting) : Scene::Scene(lastScene, renderer, width, height, filename)
{
    // si lastScene no es de tipo B, lanza un error.
    this->board = board;
    this->pawnPromoting = pawnPromoting;
}

void PawnPromotionScene::render()
{
    if (board->isWhiteTurn())
    {
        int x = pawnPromoting.col * 75;
        int y = pawnPromoting.row * 75;
        int w = 75;
        int h = 300;
        importImageInRender(renderer, "assets/images/pawnpromotion.png", x, y, w, h);
        SDL_RenderPresent(renderer);
    }
    else
    {
        int x = pawnPromoting.col * 75;
        int y = (pawnPromoting.row - 3) * 75;
        int w = 100;
        int h = 300;
        importImageInRender(renderer, "assets/images/pawnpromotion.png", x, y, w, h);
        SDL_RenderPresent(renderer);
    }
}

Scene *PawnPromotionScene::HandleEvent(SDL_Point click)
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    if (board->isWhiteTurn())
    {
        x = pawnPromoting.col * 75;
        y = pawnPromoting.row * 75;
        w = 75;
        h = 300;

    }
    else
    {
        x = pawnPromoting.col * 75;
        y = (pawnPromoting.row - 3) * 75;
        w = 100;
        h = 300;

    }

    int mx = click.x;
    int my = click.y;

    if (mx >= x && mx < x + w && my >= y && my < y + h)
    {
        switch (my / 75)
        {
        case 4:
            board->PawnPromotion(pawnPromoting, 3, board->isWhiteTurn()); // QUEEN
            break;
        case 5:
            board->PawnPromotion(pawnPromoting, 6, board->isWhiteTurn()); // KNIGHT
            break;
        case 6:
            board->PawnPromotion(pawnPromoting, 4, board->isWhiteTurn()); // ROOK
            break;
        case 7:
            board->PawnPromotion(pawnPromoting, 5, board->isWhiteTurn()); // BISHOP
            break;
        default:
            break;
        }
    }
        
    board->turnOver();
    return lastScene;

}