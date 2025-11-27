#ifndef EXITSCENE_H
#define EXITSCENE_H
#include "Scene.h"
#include "board.h"


class EndGameScene : public Scene {
public:
    using Scene::Scene;
    Scene* HandleEvent(SDL_Point click) override;
    ~EndGameScene() override = default;
};

#endif
