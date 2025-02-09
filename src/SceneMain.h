#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Scene.h"
#include "Object.h"
#include <list>


class Game;

class SceneMain : public Scene {
public:
    SceneMain();
    ~SceneMain();

    void update(float deltaTime) override;
    void render() override;
    void handleEvent(SDL_Event* event) override;
    void init() override;
    void clean() override;

    void keyboardControl(float deltaTime);
    void shootPlayer();
    void updatePlayerProjectiles(float deltaTime);
    void renderPlayerProjectiles();

private:
    Game &game;
    Player player;
    // 创建每个物体的模版
    ProjectilePlayer projectilePlayerTemplate;

    std::list<ProjectilePlayer*> projectilesPlayer;
    
};


#endif // SCENE_MAIN_H