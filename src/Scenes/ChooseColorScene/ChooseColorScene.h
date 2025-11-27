#ifndef CHOOSECOLORSCENE_H
#define CHOOSECOLORSCENE_H
#include "Scene.h"


class ChooseColorScene : public Scene {
public:
    using Scene::Scene;
    bool render() override;
    Scene* HandleEvent(SDL_Point click) override;
    ~ChooseColorScene() override = default;
};

#endif
