#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

void importImageInRender(SDL_Renderer *renderer, const std::string &route, int x, int y, int width, int height);
SDL_Point userInput();

#endif