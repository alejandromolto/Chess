#include <iostream>
#include "ForfeitScene.h"
#include "utils.h"
#include "GameScene.h"
#include "SaveMatchScene.h"

Scene* ForfeitScene::HandleEvent(SDL_Point click)
{
    int mx = click.x;
    int my = click.y;


    if (mx > width / 2 - 150 && mx < width / 2 - 150 + 100 && my > height / 2 + 120 && my < height / 2 + 120 + 100)
    {
        BScene* tps = dynamic_cast<BScene*>(lastScene);
        if (tps != 0) 
        {
            Board tempBoard = tps->getBoard();
            Scene* gameScene = new SaveMatchScene(this, renderer, width, height, filename, "assets/images/downloadboard.png", tempBoard);
            delete lastScene;
            return gameScene; // POSSIBLE MEMORY LEAK
        }
        else
        {
            return lastScene;
        }
        
    }
    else if (mx > width / 2 + 50 && mx < width / 2 + 50 + 100 && my > height / 2 + 120 && my < height / 2 + 120 + 100)
    {
        BScene* tps = dynamic_cast<BScene*>(lastScene);
        if (tps != 0) 
        {
            tps->setPhase(1); // If it is a BScene, it goes back to phase 1, (no piece selected).
            return tps;
        }
        else
        {
            return lastScene;
        }
    }else if(mx == -1 && my == -1)
    {
        return nullptr;
    }
    else{
        return this;
    }
}

