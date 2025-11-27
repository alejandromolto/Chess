#ifndef CHOOSEMATCHSCENE_H
#define CHOOSEMATCHSCENE_H
#include "Scene.h"


class ChooseMatchScene : public Scene {
public:
    using Scene::Scene;
    bool render() override;
    Scene* HandleEvent(SDL_Point click) override;
    ~ChooseMatchScene() override = default;
};

#endif
