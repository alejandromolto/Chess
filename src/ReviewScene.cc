#include <iostream>
#include "ReviewScene.h"

ReviewScene::ReviewScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename, int numBoard) : Scene::Scene(lastScene, renderer, width, height, filename){
    this->numBoard = numBoard;
}

void ReviewScene::render(){

}

Scene* ReviewScene::HandleEvent(SDL_Point click){

}