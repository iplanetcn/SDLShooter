#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Scene.h"
#include "Object.h"
#include <list>
#include <random>


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
    void spawEnemy();
    void updateEnemies(float deltaTime);
    void renderEnemies();

private:
    Game &game;
    Player player;
    std::mt19937 gen; // 随机数生成器
    std::uniform_real_distribution<float> dis; // 随机数分布器
    // 创建每个物体的模版
    Enemy enemyTemplate;
    ProjectilePlayer projectilePlayerTemplate;

    // 创建每个物体的容器
    std::list<Enemy*> enemies;
    std::list<ProjectilePlayer*> projectilesPlayer;
    
};


#endif // SCENE_MAIN_H