#ifndef ENDGAMESCENE_H
#define ENDGAMESCENE_H
#include "Scene.h"
#include "board.h"


class EndGameScene : public Scene {
private:
    // There is two variables instead of one because the situation of stalemate (nobody won) is possible in chess.
    bool whiteWon; 
    bool blackWon;
public:
    using Scene::Scene;
    EndGameScene(Scene* lastScene, SDL_Renderer* renderer, int width, int height, std::string filename, bool whiteWon, bool blackWon);
    Scene* HandleEvent(SDL_Point click) override;
    void render() override;
    ~EndGameScene() override = default;
};

#endif
