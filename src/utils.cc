
#include "include/utils.h"

void importImageInRender(SDL_Renderer *renderer, const std::string &route, int x, int y, int width, int height)
{
    SDL_Surface *surface = IMG_Load(route.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect image = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &image);
    SDL_DestroyTexture(texture);
}
