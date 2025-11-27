#include <iostream>
#include "ExitScene.h"
#include "utils.h"
#include "SaveMatchScene.h"
#include "EndGameScene.h"
#include "MainMenuScene.h"
#include "TwoPlayerScene.h"


EndGameScene::EndGameScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename, bool whiteWon, bool blackWon) : Scene(lastScene, renderer, width, height, filename){
    this->whiteWon = whiteWon;
    this->blackWon = blackWon;
}

bool EndGameScene::render()
{

    if(whiteWon){
        importImageInRender(renderer, "assets/images/WhiteWins.png", 0, 0, width, height);
    }else if(blackWon){
        importImageInRender(renderer, "assets/images/BlackWins.png", 0, 0, width, height);
    }else{
        importImageInRender(renderer, "assets/images/Stalemate.png", 0, 0, width, height);
    }

    importImageInRender(renderer, "assets/images/close.png", width - width / 50 - width / 12, height / 50, width / 12, width / 12);    
    importImageInRender(renderer, "assets/images/PlayAgain.png", width / 3 - 150, height * 2 / 3 - 150, 300, 300);
    importImageInRender(renderer, "assets/images/MainMenu.png", width * 2 / 3 - 150, height * 2 / 3 - 150, 300, 300);
    SDL_RenderPresent(renderer);

    return true;
}

Scene* EndGameScene::HandleEvent(SDL_Point click)
{
int mx = click.x;
int my = click.y;

if (mx == -1 && my == -1)
{
    return nullptr;
}

if (mx >= width - width / 50 - width / 12 && mx <= width - width / 50 && my >= height / 50 && my <= height / 50 + width / 12)
{
    return nullptr;
}
else if (mx >= width / 3 - 150 && mx <= width / 3 + 150 && my >= height * 2 / 3 - 150 && my <= height * 2 / 3 + 150)
{
    return new TwoPlayerScene(this, renderer, width, height, filename);
}
else if (mx >= width * 2 / 3 - 150 && mx <= width * 2 / 3 + 150 && my >= height * 2 / 3 - 150 && my <= height * 2 / 3 + 150)
{
    return new MainMenuScene(this, renderer, width, height, filename);
}

return this;
}

