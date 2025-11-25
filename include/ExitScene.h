#ifndef EXITSCENE_H
#define EXITSCENE_H
#include "Scene.h"
#include "ConfirmationScene.h"
#include "board.h"


class ExitScene : public ConfirmationScene {
public:
    using ConfirmationScene::ConfirmationScene;
    Scene* HandleEvent(SDL_Point click) override;
};

#endif
