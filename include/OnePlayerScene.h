#ifndef ONEPLAYERSCENE_H
#define ONEPLAYERSCENE_H
#include "Scene.h"
#include "BScene.h"
#include "AI.h"

class OnePlayerScene : public BScene {
private:
    bool isAiWhite;
    AI* aiPlayer;
public:
    OnePlayerScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename, bool isAiWhite);
    void render() override;
    Scene* HandleEvent(SDL_Point click) override;
};

#endif
