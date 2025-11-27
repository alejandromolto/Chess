#ifndef SAVEMATCHSCENE_H
#define SAVEMATCHSCENE_H
#include "Scene.h"
#include "ConfirmationScene.h"
#include "board.h"


class SaveMatchScene : public ConfirmationScene {
private:
    Board board;
public:
    SaveMatchScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename, std::string imageRoute, const Board& board);
    using ConfirmationScene::ConfirmationScene;
    Scene* HandleEvent(SDL_Point click) override;
    ~SaveMatchScene() override = default;
};

#endif
