#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Scene{
protected:
    Scene* lastScene = nullptr; 
    SDL_Renderer* renderer = nullptr;
    int width = 0;
    int height = 0;
public:
    Scene(Scene* lastScene, SDL_Renderer* renderer, int width, int height);
    Scene(Scene* Scene);

    virtual void render();
    virtual Scene* HandleEvent(SDL_Point click);
    Scene* getLastScene(){return lastScene; }
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    SDL_Renderer* getRenderer(){ return renderer;}
};

#endif