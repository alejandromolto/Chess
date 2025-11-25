#ifndef OPTIONSMENUSCENE_H
#define OPTIONSMENUSCENE_H
#include "Scene.h"


class OptionsMenuScene : public Scene {
private:
    int optionWidth;
    int optionHeight;
public:
    OptionsMenuScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height);
    void render() override;
    Scene* HandleEvent(SDL_Point click) override;
};

#endif
