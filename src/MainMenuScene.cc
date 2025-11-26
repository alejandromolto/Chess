#include "Scene.h"
#include <iostream>
#include "MainMenuScene.h"
#include "OptionsMenuScene.h"
#include "ChooseMatchScene.h"
#include "utils.h"
#include "TwoPlayerScene.h"
#include "OnePlayerScene.h"
#include "ChooseColorScene.h"

void MainMenuScene::render(){
    importImageInRender(renderer, "assets/images/mainbackground.png", 0, 0, width, height);
    importImageInRender(renderer, "assets/images/singleplayer.png", width / 3 - 20, height / 8 * 3, width / 6, width / 6);
    importImageInRender(renderer, "assets/images/twoplayers.png", width / 2 + width / 24 - 20, height / 8 * 3, width / 6, width / 6);
    importImageInRender(renderer, "assets/images/reviewgames.png", width / 3 - 20, height / 8 * 6, width * 3 / 8, height / 5);
    importImageInRender(renderer, "assets/images/close.png", width - width / 50 - width / 12, height / 50, width / 12, width / 12);
    importImageInRender(renderer, "assets/images/burguerSettings.png", width - (width / 50) - (width / 12) - (width / 50) - (width / 11.52), height / 50, width / 11.52, width / 11.52);
    SDL_RenderPresent(renderer);
}

Scene* MainMenuScene::HandleEvent(SDL_Point click){

    int mx = click.x;
    int my = click.y;

    if (mx > width / 3 - 20 && mx < width / 3 - 20 + width / 6 && my > height / 8 * 3 && my < height / 8 * 3 + width / 6)
    {
        return new ChooseColorScene(this, renderer, width, height, filename);
    }
    else if (mx > width / 2 + width / 24 - 20 && mx < width / 2 + width / 24 - 20 + width / 6 && my > height / 8 * 3 && my < height / 8 * 3 + width / 6)
    {
        return new TwoPlayerScene(this, renderer, width, height, filename);
    }
    else if (mx > width / 3 - 20 && mx < width / 3 - 20 + width * 3 / 8 && my > height / 8 * 6 && my < height / 8 * 6 + height / 5)
    {
        return new ChooseMatchScene(this, renderer, width, height, filename);
    }
    else if (mx > width - (width / 50) - (width / 12) - (width / 50) - (width / 11.52) && mx < width - (width / 50) - (width / 12) - (width / 50) - (width / 11.52) + width / 11.52 && my > height / 50 && my < height / 50 + width / 11.52)
    {
        return new OptionsMenuScene(this, renderer, width, height, filename);
    }
    else if (mx > width - width / 50 - width / 12 && mx < width - width / 50 - width / 12 + width / 12 && my > height / 50 && my < height / 50 + width / 12)
    {
        delete lastScene;
        return nullptr;
    }else{
        return this;
    }

}