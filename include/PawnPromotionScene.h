#ifndef PAWNPROMOTIONSCENE_H
#define PAWNPROMOTIONSCENE_H
#include "Scene.h"
#include "ConfirmationScene.h"
#include "board.h"
#include <SDL2/SDL.h>


class PawnPromotionScene : public Scene {
private:
    Board* board;
    T_Coordinates pawnPromoting;
public:
    PawnPromotionScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename, Board* board, T_Coordinates pawnPromoting);
    void render();
    Scene* HandleEvent(SDL_Point click) override;
};

#endif
