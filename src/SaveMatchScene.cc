#include <iostream>
#include "ForfeitScene.h"
#include "utils.h"
#include "BScene.h"
#include "SaveMatchScene.h"
#include "MainMenuScene.h"
#include "exporter.h"

SaveMatchScene::SaveMatchScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename, std::string imageRoute, const Board& board): ConfirmationScene(lastScene, renderer, width, height, filename, imageRoute){
    this->board = board;
}

Scene* SaveMatchScene::HandleEvent(SDL_Point click)
{
    int mx = click.x;
    int my = click.y;


    if (mx > width / 2 - 150 && mx < width / 2 - 150 + 100 && my > height / 2 + 120 && my < height / 2 + 120 + 100)
    {
        Exporter exp;
        exp.exportGametoFile(board, filename); 
    }

    delete lastScene;
    return new MainMenuScene(this, renderer, width, height, filename);
}

