#ifndef CONFIRMATIONSCENE_H
#define CONFIRMATIONSCENE_H
#include "Scene.h"
#include "board.h"

class ConfirmationScene : public Scene {
public:
    ConfirmationScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename, std::string imageRoute);
    void render() override;
    ~ConfirmationScene() override = default;

protected:
    std::string imageRoute;
};

#endif
