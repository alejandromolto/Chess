#include "Scene.h"
#include "utils.h"


    Scene::Scene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename){
        this->lastScene = lastScene;
        this->renderer = renderer;
        this->width = width;
        this->height = height;
        this->filename = filename;
    }

    Scene::Scene(Scene* Scene){
        this->lastScene = Scene->getLastScene();
        this->renderer = Scene->getRenderer();
        this->width = Scene->getWidth();
        this->height = Scene->getHeight();
    }
