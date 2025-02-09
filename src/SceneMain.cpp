#include "SceneMain.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <random>

SceneMain::SceneMain() : game(Game::getInstance())
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::update(float deltaTime)
{
    keyboardControl(deltaTime);
    updatePlayerProjectiles(deltaTime);
    spawEnemy();
    updateEnemies(deltaTime);
}

void SceneMain::render()
{
    // 渲染玩家子弹
    renderPlayerProjectiles();
    // 渲染玩家
    SDL_Rect playerRect = { static_cast<int>(player.position.x), 
                            static_cast<int>(player.position.y), 
                            player.width, 
                            player.height };
    SDL_RenderCopy(game.getRenderer(), player.texture, NULL, &playerRect);
    // 渲染敌人
    renderEnemies();
    
}

void SceneMain::handleEvent(SDL_Event *event)
{
}

void SceneMain::init()
{
    std::random_device rd;
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<float>(0.0f, 1.0f);
    
    player.texture = IMG_LoadTexture(game.getRenderer(), "assets/image/SpaceShip.png");
    if (player.texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load player texture: %s", SDL_GetError());
    }
    SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
    player.width /= 4;
    player.height /= 4;
    player.position.x = game.getWindowWidth() / 2 - player.width / 2;
    player.position.y = game.getWindowHeight() - player.height;

    // 初始化模版
    projectilePlayerTemplate.texture = IMG_LoadTexture(game.getRenderer(), "assets/image/laser-1.png");
    SDL_QueryTexture(projectilePlayerTemplate.texture, NULL, NULL, &projectilePlayerTemplate.width, &projectilePlayerTemplate.height);
    projectilePlayerTemplate.width /= 4;
    projectilePlayerTemplate.height /= 4;

    enemyTemplate.texture = IMG_LoadTexture(game.getRenderer(), "assets/image/insect-2.png");
    SDL_QueryTexture(enemyTemplate.texture, NULL, NULL, &enemyTemplate.width, &enemyTemplate.height);
    enemyTemplate.width /= 4;
    enemyTemplate.height /= 4;
}

void SceneMain::clean()
{
    // 清理容器
    for (auto &projectile : projectilesPlayer){
        if (projectile != nullptr){
            delete projectile;
        }
    }
    projectilesPlayer.clear();

    for (auto &enemy : enemies){
        if (enemy != nullptr){
            delete enemy;
        }
    }
    enemies.clear();

    // 清理模版
    if (player.texture != nullptr)
    {
        SDL_DestroyTexture(player.texture);
    }
    if (projectilePlayerTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(projectilePlayerTemplate.texture);
    }
    if (enemyTemplate.texture != nullptr){
        SDL_DestroyTexture(enemyTemplate.texture);
    }
}

void SceneMain::keyboardControl(float deltaTime)
{
    auto keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_W]){
        player.position.y -= deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_S]){
        player.position.y += deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_A]){
        player.position.x -= deltaTime * player.speed;
    }
    if (keyboardState[SDL_SCANCODE_D]){
        player.position.x += deltaTime * player.speed;
    }
    
    // 限制飞机的移动范围
    if (player.position.x < 0){
        player.position.x = 0;
    }
    if (player.position.x > game.getWindowWidth() - player.width){
        player.position.x = game.getWindowWidth() - player.width;
    }
    if (player.position.y < 0){
        player.position.y = 0;
    }
    if (player.position.y > game.getWindowHeight() - player.height){
        player.position.y = game.getWindowHeight() - player.height;
    }

    // 控制子弹发射
    if (keyboardState[SDL_SCANCODE_J]){
        auto currentTime = SDL_GetTicks();
        if (currentTime - player.lastShootTime > player.coolDown){
            shootPlayer();
            player.lastShootTime = currentTime;
        }
    }
        
}

void SceneMain::shootPlayer()
{
    // 在这里实现发射子弹的逻辑
    auto projectile = new ProjectilePlayer(projectilePlayerTemplate);
    projectile->position.x = player.position.x + player.width / 2 - projectile->width / 2;
    projectile->position.y = player.position.y;
    projectilesPlayer.push_back(projectile);
}

void SceneMain::updatePlayerProjectiles(float deltaTime)
{
    int margin = 32; // 子弹超出屏幕外边界的距离
    for (auto it = projectilesPlayer.begin(); it != projectilesPlayer.end();){
        auto projectile = *it;
        projectile->position.y -= projectile->speed * deltaTime;
        // 检查子弹是否超出屏幕
        if (projectile->position.y + margin < 0){
            delete projectile;
            it = projectilesPlayer.erase(it);
        }else {
            ++it;
        }
    }
}

void SceneMain::renderPlayerProjectiles()
{
    for (auto projectile : projectilesPlayer){
        SDL_Rect projectileRect = {
            static_cast<int>(projectile->position.x),
            static_cast<int>(projectile->position.y),
            projectile->width,
            projectile->height
        };
        SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &projectileRect);
    }
}

void SceneMain::spawEnemy()
{
    if (dis(gen) > 1 / 60.0f){
        return;
    }
    Enemy* enemy = new Enemy(enemyTemplate);
    enemy->position.x = dis(gen) * (game.getWindowWidth() - enemy->width);
    enemy->position.y = - enemy->height;
    enemies.push_back(enemy);
}

void SceneMain::updateEnemies(float deltaTime)
{
    for (auto it = enemies.begin(); it != enemies.end();){
        auto enemy = *it;
        enemy->position.y += enemy->speed * deltaTime;
        if (enemy->position.y > game.getWindowHeight()){
            delete enemy;
            it = enemies.erase(it);
        }else {
            ++it;
        }
    }
}

void SceneMain::renderEnemies()
{
    for (auto enemy : enemies){
        SDL_Rect enemyRect = {
            static_cast<int>(enemy->position.x),
            static_cast<int>(enemy->position.y),
            enemy->width,
            enemy->height
        };
        SDL_RenderCopy(game.getRenderer(), enemy->texture, NULL, &enemyRect);
    }
}
