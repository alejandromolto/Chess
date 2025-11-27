#include <iostream>
#include "ReviewScene.h"
#include "utils.h"
#include "importer.h"
#include "MainMenuScene.h"
#include <iostream>

ReviewScene::ReviewScene(Scene *lastScene, SDL_Renderer *renderer, int width, int height, std::string filename, int matchpointer) : Scene::Scene(lastScene, renderer, width, height, filename)
{
    boardpointer = 0;
    Importer i;
    i.importGametoBoard(filename, matchpointer-1);
    this->game = i.gethistory();
}

void ReviewScene::render()
{

    importImageInRender(renderer, "assets/images/greyColor.png", 0, 0, width, height);
    importImageInRender(renderer, "assets/images/greyColor.png", 0, 0, width, height); // Match background
    importImageInRender(renderer, "assets/images/Leftarrow.png", 600 + 10, 600 - 200, 200, 200);
    importImageInRender(renderer, "assets/images/Rightarrow.png", 600 + 210, 600 - 200, 200, 200);
    importImageInRender(renderer, "assets/images/back.png", width - width / 50 - width / 12, height / 50, width / 12, width / 12);

    int gameBoard[8][8];
    int cont = 0;

    for (int i = 0; i < 8; i++)
    { // Decompress
        for (int j = 0; j < 8; j++)
        {
            gameBoard[i][j] = game[boardpointer][cont];
            cont++;
        }
    }

    Board board;
    board.setboard(gameBoard);
    board.printboard(600, 600, renderer);
    SDL_RenderPresent(renderer);
}

Scene *ReviewScene::HandleEvent(SDL_Point click)
{
    int mx = click.x;
    int my = click.y;

    if (my == -1 && mx == -1)
    {
        return nullptr; // MEMORY LEAK
    }

    if (mx > 600 + 10 && mx < 600 + 10 + 200 && my > 600 - 200 && my < 600 - 200 + 200)
    {
        boardpointer--;
        return this;
    }
    else if (mx > 600 + 210 && mx < 600 + 210 + 200 && my > 600 - 200 && my < 600 - 200 + 200)
    {
        boardpointer++;
        if(boardpointer == game.size()){
           return new MainMenuScene(this, renderer, width, height, filename);
        }
        return this;
    }
    else if (mx > width - width / 50 - width / 12 && mx < width - width / 50 - width / 12 + width / 12 && my > height / 50 && my < height / 50 + width / 12)
    {
        return new MainMenuScene(this, renderer, width, height, filename);
    }else{
        return this;
    }
}