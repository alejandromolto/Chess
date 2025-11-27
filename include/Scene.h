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
    std::string filename;
public:
    Scene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename);
    Scene(Scene* Scene);

    virtual void render() = 0;
    virtual Scene* HandleEvent(SDL_Point click) = 0;
    Scene* getLastScene(){return lastScene; }
    void setLastScene(Scene* lastScene){ this->lastScene = lastScene; }
    void setWidth(int width){this->width = width; }
    void setHeight(int height){ this->height = height; }
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    SDL_Renderer* getRenderer(){ return renderer;}
    virtual ~Scene() = default;
};

#endif