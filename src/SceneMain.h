#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Scene.h"
#include "Object.h"
#include <list>
#include <random>
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>


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
    void updatePlayer(float deltaTime);
    void renderEnemies();
    void shootEnemy(Enemy* enemy);
    SDL_FPoint getDirection(Enemy* enemy);
    void enemyExplode(Enemy* enemy);
    void updateExplosions(float deltaTime);
    void renderExplosions();
    void dropItem(Enemy* enemy);
    void updateItems(float deltaTime);
    void playerGetItem(Item* item);
    void renderItems();
    void renderUI();

private:
    Game &game;
    Player player;
    Mix_Music* bgm;
    SDL_Texture* uiHealth;

    bool isDead = false; // 玩家是否死亡
    std::mt19937 gen; // 随机数生成器
    std::uniform_real_distribution<float> dis; // 随机数分布器
    // 创建每个物体的模版
    Enemy enemyTemplate;
    ProjectilePlayer projectilePlayerTemplate;
    ProjectileEnemy projectileEnemyTemplate;
    Explosion explosionTemplate;
    Item itemLifeTemplate;

    // 创建每个物体的容器
    std::list<Enemy*> enemies;
    std::list<ProjectilePlayer*> projectilesPlayer;
    std::list<ProjectileEnemy*> projectilesEnemy;
    std::list<Explosion*> explosions;
    std::list<Item*> items;
    std::map<std::string, Mix_Chunk*> sounds; // 存储音效
    
};


#endif // SCENE_MAIN_H