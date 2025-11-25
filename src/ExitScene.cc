#include <iostream>
#include "ExitScene.h"
#include "utils.h"
#include "BScene.h"
#include "SaveMatchScene.h"

Scene* ExitScene::HandleEvent(SDL_Point click)
{
    int mx = click.x;
    int my = click.y;


    if (mx > width / 2 - 150 && mx < width / 2 - 150 + 100 && my > height / 2 + 120 && my < height / 2 + 120 + 100)
    {
        delete lastScene;
        return new SaveMatchScene(this, renderer, width, height, filename, "assets/images/downloadboard.png");
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
    }
}

