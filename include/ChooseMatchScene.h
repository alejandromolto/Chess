#ifndef CHOOSEMATCHSCENE_H
#define CHOOSEMATCHSCENE_H
#include "Scene.h"


class ChooseMatchScene : public Scene {
public:
    ChooseMatchScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height);
    void render() override;
    Scene* HandleEvent(SDL_Point click) override;
};

#endif
