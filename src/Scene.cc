#include "Scene.h"
#include "utils.h"


    Scene::Scene(Scene* lastScene, SDL_Renderer* renderer, int width, int height){
        this->lastScene = lastScene;
        this->renderer = renderer;
        this->width = width;
        this->height = height;
    }

    Scene::Scene(Scene* Scene){
        this->lastScene = Scene->getLastScene();
        this->renderer = Scene->getRenderer();
        this->width = Scene->getWidth();
        this->height = Scene->getHeight();
    }

    void Scene::render(){
    }

    Scene* Scene::HandleEvent(SDL_Point click){
    }