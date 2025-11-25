#ifndef TWOPLAYERSCENE_H
#define TWOPLAYERSCENE_H
#include "Scene.h"
#include "BScene.h"

class TwoPlayerScene : public BScene {
private:
public:
    using BScene::BScene;
    // TwoPlayerScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename);
    void render() override;
    Scene* HandleEvent(SDL_Point click) override;
};

#endif
