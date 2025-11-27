#include <iostream>
#include "ReviewScene.h"
#include "utils.h"
#include "importer.h"
#include "MainMenuScene.h"
#include "ConfirmationScene.h"
#include <iostream>

ConfirmationScene::ConfirmationScene(Scene *lastScene, SDL_Renderer *renderer, int width, int height, std::string filename, std::string imageRoute) : Scene::Scene(lastScene, renderer, width, height, filename)
{
    this->imageRoute = imageRoute;
}


bool ConfirmationScene::render()
{
    importImageInRender(renderer, imageRoute, width / 2 - 200, height / 2 - 200, 400, 400);
    importImageInRender(renderer, "assets/images/yes.png", width / 2 - 150, height / 2 + 120, 100, 100);
    importImageInRender(renderer, "assets/images/no.png", width / 2 + 50, height / 2 + 120, 100, 100);
    SDL_RenderPresent(renderer);

    return true;
}

