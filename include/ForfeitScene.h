#ifndef FORFEITSCENE_H
#define FORFEITSCENE_H
#include "Scene.h"
#include "ConfirmationScene.h"
#include "board.h"
#include <SDL2/SDL.h>


class ForfeitScene : public ConfirmationScene {
public:
    using ConfirmationScene::ConfirmationScene;
    Scene* HandleEvent(SDL_Point click) override;
    ~ForfeitScene() override = default;
};

#endif
