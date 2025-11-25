#include <iostream>
#include "ChooseMatchScene.h"
#include "utils.h"
#include "importer.h"
#include "exporter.h"

void ChooseMatchScene::render()
{
    importImageInRender(renderer, "assets/images/ChooseGameBackground.png", 0, 0, width, height);
    importImageInRender(renderer, "assets/images/deleteFiles.png", width - std::max(20, width / 64) - std::max(100, std::min(width / 8, height / 8)), height - std::max(20, width / 64) - std::max(100, std::min(width / 8, height / 8)), std::max(100, std::min(width / 8, height / 8)), std::max(100, std::min(width / 8, height / 8)));
    importImageInRender(renderer, "assets/images/back.png", width - width / 50 - width / 12, height / 50, width / 12, width / 12);

    Importer import;
    int ngames = import.howManyGames(filename);

    for (int i = 0; i < 10; i++)
    {
        std::string numberfile = "assets/images/";
        numberfile += std::to_string((i + 1));
        numberfile += ".png";
        importImageInRender(renderer,
                            numberfile,
                            width / 4 + (width / 4) * (i % 2) + 5 * (i % 2) + 45,
                            (height / 6) * (i / 2) + height / 6 + 5 * (i / 2),
                            width / 8,
                            height / 12);

        if (i < ngames)
        {
            SDL_Rect greenSquare;
            greenSquare.x = width / 4 + (width / 4) * (i % 2) + 5 * (i % 2) + 45;
            greenSquare.y = (height / 6) * (i / 2) + height / 6 + 5 * (i / 2);
            greenSquare.w = width / 8;
            greenSquare.h = height / 12;
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
            SDL_RenderFillRect(renderer, &greenSquare);
        }
    }
    SDL_RenderPresent(renderer);
}

Scene *ChooseMatchScene::HandleEvent(SDL_Point click)
{
    int mx = click.x;
    int my = click.y;

    Importer import;
    int ngames = import.howManyGames(filename);
    if (mx == -1 && my == -1)
    {
        return nullptr; // MEMORY LEAK
    }
    else
    {

        if (mx > width / 4 + 45 && mx < width / 4 + 45 + width / 8 && my > height / 6 && my < height / 6 + height / 12 && ngames > 0)
            std::cout << ":)" << std::endl;
            // 1
        else if (mx > width / 2 + 50 && mx < width / 2 + 50 + width / 8 && my > height / 6 && my < height / 6 + height / 12 && ngames > 1)
            std::cout << ":)" << std::endl;
            // 2
        else if (mx > width / 4 + 45 && mx < width / 4 + 45 + width / 8 && my > height / 3 + 5 && my < height / 3 + 5 + height / 12 && ngames > 2)
            std::cout << ":)" << std::endl;
            // 3
        else if (mx > width / 2 + 50 && mx < width / 2 + 50 + width / 8 && my > height / 3 + 5 && my < height / 3 + 5 + height / 12 && ngames > 3)
            std::cout << ":)" << std::endl;
            // 4
        else if (mx > width / 4 + 45 && mx < width / 4 + 45 + width / 8 && my > height / 2 + 10 && my < height / 2 + 10 + height / 12 && ngames > 4)
            std::cout << ":)" << std::endl;
            // 5
        else if (mx > width / 2 + 50 && mx < width / 2 + 50 + width / 8 && my > height / 2 + 10 && my < height / 2 + 10 + height / 12 && ngames > 5)
            std::cout << ":)" << std::endl;
            // 6
        else if (mx > width / 4 + 45 && mx < width / 4 + 45 + width / 8 && my > height * 2 / 3 + 15 && my < height * 2 / 3 + 15 + height / 12 && ngames > 6)
            std::cout << ":)" << std::endl;
            // 7
        else if (mx > width / 2 + 50 && mx < width / 2 + 50 + width / 8 && my > height * 2 / 3 + 15 && my < height * 2 / 3 + 15 + height / 12 && ngames > 7)
            std::cout << ":)" << std::endl;
            // 8
        else if (mx > width / 4 + 45 && mx < width / 4 + 45 + width / 8 && my > height * 5 / 6 + 20 && my < height * 5 / 6 + 20 + height / 12 && ngames > 8)
            std::cout << ":)" << std::endl;
            // 9
        else if (mx > width / 2 + 50 && mx < width / 2 + 50 + width / 8 && my > height * 5 / 6 + 20 && my < height * 5 / 6 + 20 + height / 12 && ngames > 1)
            std::cout << ":)" << std::endl;
            // 10
        else if (mx >= width - std::max(20, width / 64) - std::max(100, std::min(width / 8, height / 8)) && mx < width - std::max(20, width / 64) &&
                 my >= height - std::max(20, width / 64) - std::max(100, std::min(width / 8, height / 8)) && my < height - std::max(20, width / 64))
        {
            // delete files
            Exporter exp;
            exp.emptyFile(filename);
            lastScene->setLastScene(this);
            return lastScene;
        }
        else if (mx > width - width / 50 - width / 12 && mx < width - width / 50 - width / 12 + width / 12 && my > height / 50 && my < height / 50 + width / 12)
        {
            lastScene->setLastScene(this);
            return lastScene;
        }else{
            return this;
        }
    }
}