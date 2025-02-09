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
    void renderEnemyProjectiles();
    void spawEnemy();
    void updateEnemies(float deltaTime);
    void updateEnemyProjectiles(float deltaTime);
    void renderEnemies();
    void shootEnemy(Enemy* enemy);
    SDL_FPoint getDirection(Enemy* enemy);

private:
    Game &game;
    Player player;
    std::mt19937 gen; // 随机数生成器
    std::uniform_real_distribution<float> dis; // 随机数分布器
    // 创建每个物体的模版
    Enemy enemyTemplate;
    ProjectilePlayer projectilePlayerTemplate;
    ProjectileEnemy projectileEnemyTemplate;

    // 创建每个物体的容器
    std::list<Enemy*> enemies;
    std::list<ProjectilePlayer*> projectilesPlayer;
    std::list<ProjectileEnemy*> projectilesEnemy;
    
};


#endif // SCENE_MAIN_H