#ifndef REVIEWSCENE_H
#define REVIEWSCENE_H
#include "Scene.h"
#include <vector>

class ReviewScene : public Scene {
private: 
    std::vector<std::vector<int>> game;
    int boardpointer;
public:
    ReviewScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename, int matchpointer);
    void render() override;
    Scene* HandleEvent(SDL_Point click) override;
};

#endif
