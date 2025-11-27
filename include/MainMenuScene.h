#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H
#include "Scene.h"


class MainMenuScene : public Scene {
public:
    using Scene::Scene;
    bool render() override;
    Scene* HandleEvent(SDL_Point click) override;
    ~MainMenuScene() override = default;
};

#endif
