#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include "include/utils.h"
#include "include/board.h"
#include "exporter.h"
#include "importer.h"
#include "AI.h"
#include "Scene.h"
#include "MainMenuScene.h"

int main()
{

    // Variables initialization
    int width = 1152;
    int height = 680;
    std::string filename = "chessMatches.txt";
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    bool running = true;

    // CODE

    Scene* currentScene = new MainMenuScene(nullptr, renderer, width, height, filename);

    while (running){
        currentScene->render();
        SDL_Point click = userInput();
        currentScene = currentScene->HandleEvent(click);
        std::cout << currentScene << std::endl;
        if(currentScene == nullptr){
            break;
        }
        if(width != currentScene->getLastScene()->getWidth() || height != currentScene->getLastScene()->getHeight()){
            width = currentScene->getLastScene()->getWidth();
            height = currentScene->getLastScene()->getHeight();
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            currentScene = new MainMenuScene(nullptr, renderer, width, height, filename);
        }
    }

    // END

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// TODO: ERASE MEMORY LEAKS IN MAINMENUSCENE
// TODO: ERASE MEMORY LEAKS IN OPTIONSMENUSCENE 


