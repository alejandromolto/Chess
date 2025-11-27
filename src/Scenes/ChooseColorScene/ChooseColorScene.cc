#include <iostream>
#include "ChooseMatchScene.h"
#include "utils.h"
#include "importer.h"
#include "exporter.h"
#include "ReviewScene.h"
#include "ChooseColorScene.h"
#include "OnePlayerScene.h"

bool ChooseColorScene::render()
{
    importImageInRender(renderer, "assets/images/chooseColor.png", 0, 0, (width), (height));
    importImageInRender(renderer, "assets/images/blackwhite.png", (width / 3), (height / 4), (width / 3), (height / 3));
    SDL_RenderPresent(renderer);

    return true;
}

Scene *ChooseColorScene::HandleEvent(SDL_Point click)
{
    int mx = click.x;
    int my = click.y;



    if (mx >= width / 3 && mx <= width / 3 + (width / 6) && my >= height / 4 && my <= height / 4 + (height * 2 / 3))
    {
    // WHITE
        return new OnePlayerScene(this, renderer, width, height, filename, true);
    }
    else if (mx >= width / 3 + (width / 6) && mx <= width / 3 * 2 && my >= height / 4 && my <= height * 2 / 3)
    {
    //BLACK
        return new OnePlayerScene(this, renderer, width, height, filename, false);
    }
    else if (my == -1 && mx == -1)
    {
        return nullptr;
    }
    else{
        return this;
    }
}