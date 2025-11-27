#include "utils.h"

void importImageInRender(SDL_Renderer *renderer, const std::string &route, int x, int y, int width, int height)
{
    SDL_Surface *surface = IMG_Load(route.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect image = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &image);
    SDL_DestroyTexture(texture);
}


SDL_Point userInput()
{
    SDL_Event e;
    while (SDL_WaitEvent(&e)) {                 // block until an event arrives
        if (e.type == SDL_QUIT) {
            return { -1, -1 };                  // signal quit
        }
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            return { e.button.x, e.button.y };  // return click coords
        }
    }
    return { -1, -1 }; // in case SDL_WaitEvent fails
}