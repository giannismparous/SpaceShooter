#pragma once
#include "vector"
#include "Player.h"
#include "enemy.h"
#include "enemy2.h"
#include "bullet.h"


class Game
{
    char playerCoords[40];
    char enemiesAlive[5];
    char playerScore[40];
    graphics::Brush br;
    bool debugMode = false;
    bool aliveState = true;
    int lastTime = -3000;
    int lastTimeFired = -3000;
    int cooldown = 2000;
    int cooldown2 = 3000;
    int enemyCounter = 0;
    int enemyCounter2 = 0;
    int score = 0;
    int i = 0;
    int j = 0;
    Player* player = nullptr;
    bool player_initialized = false;
    float deathX;
    float deathY;
    float lastTimeEnemy = 0;
    float lastTimeEnemy2 = 0;
    std::vector<bullet*> bullets;
    std::vector<enemy*> enemies;
    std::vector<enemy2*> enemies2;
    std::vector<bullet*> enemyBullets;
    graphics::MouseState mouse;

public:
    bool getAliveState() { return aliveState; }
    void kill();
    void update();
    void draw();
    void enemyFire(int i);
    void init();
    Game();
    ~Game();
};