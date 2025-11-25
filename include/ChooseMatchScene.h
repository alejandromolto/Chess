#ifndef CHOOSEMATCHSCENE_H
#define CHOOSEMATCHSCENE_H
#include "Scene.h"


class ChooseMatchScene : public Scene {
public:
    using Scene::Scene;
    void render() override;
    Scene* HandleEvent(SDL_Point click) override;
};

#endif
