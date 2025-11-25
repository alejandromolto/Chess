#ifndef REVIEWSCENE_H
#define REVIEWSCENE_H
#include "Scene.h"


class ReviewScene : public Scene {
public:
    ReviewScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename);
    void render() override;
    Scene* HandleEvent(SDL_Point click) override;
};

#endif
