#ifndef ONEPLAYERSCENE_H
#define ONEPLAYERSCENE_H
#include "Scene.h"
#include "GameScene.h"
#include "AI.h"

class OnePlayerScene : public BScene {
private:
    bool isAiWhite;
public:
    OnePlayerScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename, bool isAiWhite);
    bool render() override;
    Scene* HandleEvent(SDL_Point click) override;
    std::pair<T_Coordinates, T_Coordinates> getAIMove();
    ~OnePlayerScene() override = default;
};

#endif
