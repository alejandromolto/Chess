#include "OptionsMenuScene.h"
#include "MainMenuScene.h"
#include "utils.h"
#include <iostream>

OptionsMenuScene::OptionsMenuScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename): Scene(lastScene, renderer, width, height, filename)
{
    optionWidth = width;                        
    optionHeight = height;
}

void OptionsMenuScene::render(){
    importImageInRender(renderer, "assets/images/greyColor.png", 0, 0, width, height);
    importImageInRender(renderer, "assets/images/back.png", width - (width * 72) / 720 - width / 60, height / 60, (width * 72) / 720, (width * 72) / 720);
    importImageInRender(renderer, "assets/images/linkTreeLogo.png", width - width / 50 - width / 24, height - width / 24 - height / 50, width / 24, width / 24);
    importImageInRender(renderer, "assets/images/linkedinLogo.png", width - width / 50 - width / 24 - width / 50 - width / 24, height - width / 24 - height / 50, width / 24, width / 24);

    // Options

    int x = -10;

    // RESOLUTION

    if (optionWidth == 768 && optionHeight == 453) // Small
    {
        x = 2;
    }
    else if (optionWidth == 1152 && optionHeight == 680) // Medium
    {
        x = 6;
    }
    else if (optionWidth == 1824 && optionHeight == 1026) // Big
    {
        x = 10;
    }

    importImageInRender(renderer, "assets/images/screenSize.png", (width - (width * 540) / 720) / 2, (height * 100) / 720, (width * 540) / 720, (height * 180) / 720);
    importImageInRender(renderer, "assets/images/GreySquare.png", ((width / 16) * x) + (width * 40) / 720, (height * 310) / 720, (width * 110) / 720, (width * 110) / 720);
    importImageInRender(renderer, "assets/images/smallRes.png", (width / 16) * 2 + (width * 50) / 720, (height * 320) / 720, (width * 90) / 720, (width * 90) / 720);
    importImageInRender(renderer, "assets/images/mediumRes.png", (width / 16) * 6 + (width * 50) / 720, (height * 320) / 720, (width * 90) / 720, (width * 90) / 720);
    importImageInRender(renderer, "assets/images/largeRes.png", (width / 16) * 10 + (width * 50) / 720, (height * 320) / 720, (width * 90) / 720, (width * 90) / 720);

    SDL_RenderPresent(renderer);
}

Scene* OptionsMenuScene::HandleEvent(SDL_Point click){

    int mx = click.x;
    int my = click.y;
    if (mx == -1 && my == -1)
    {
        return nullptr;
    }
    else
    {

        if (mx >= width - (width * 72) / 720 - width / 60 && mx <= width - (width * 72) / 720 - width / 60 + (width * 72) / 720 &&
            my >= height / 60 && my <= height / 60 + (width * 72) / 720)
        {

            width = optionWidth;
            height = optionHeight;
            lastScene->setLastScene(this);
            return lastScene;

        }
        else if (mx >= (width / 16) * 2 + (width * 50) / 720 && mx <= (width / 16) * 2 + (width * 50) / 720 + (width * 90) / 720 &&
                 my >= (height * 320) / 720 && my <= (height * 320) / 720 + (width * 90) / 720)
        {
            optionWidth = 768;
            optionHeight = 453;
            return this;
        }
        else if (mx >= (width / 16) * 6 + (width * 50) / 720 && mx <= (width / 16) * 6 + (width * 50) / 720 + (width * 90) / 720 &&
                 my >= (height * 320) / 720 && my <= (height * 320) / 720 + (width * 90) / 720)
        {
            optionWidth = 1152;
            optionHeight = 680;
            return this;
        }
        else if (mx >= (width / 16) * 10 + (width * 50) / 720 && mx <= (width / 16) * 10 + (width * 50) / 720 + (width * 90) / 720 &&
                 my >= (height * 320) / 720 && my <= (height * 320) / 720 + (width * 90) / 720)
        {
            optionWidth = 1824;
            optionHeight = 1026;
            return this;
        }
        else if (mx > width - (width / 50) - (width / 24) && mx < width - (width / 50) &&
                 my > height - width / 24 - height / 50 && my < height - height / 50)
        {
            system("xdg-open https://linktr.ee/alejandromolto");
            return this;
        }
        else if (mx > width - (width / 50) - (width / 24) - (width / 50) - (width / 24) &&
                 mx < width - (width / 50) - (width / 24) - (width / 50) &&
                 my > height - width / 24 - height / 50 && my < height - height / 50)
        {
            system("xdg-open https://linkedin.com/in/alejandromolto");
            return this;
        }else{
            return this;
        }
    }
}