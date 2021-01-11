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
    bool stateGame = false;
    bool shouldFire = true;
    int lastTime;
    int lastTimeFired;
    int reloadTimer;
    int cooldown;
    int cooldown2;
    int enemyCounter;
    int enemyCounter2;
    int score;
    int starttimer;
    int CountBullets = 0;
    int i;
    int j;
    Player* player = nullptr;
    bool player_initialized = false;
    bool MenuFlash = true;
    float deathX;
    float deathY;
    float lastTimeEnemy;
    float lastTimeEnemy2;
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
    void CheckCollision();
    void StartMenu();
    void GameUpdate();
    void StartMenuDraw();
    void GameUpdateDraw();
    Game();
    ~Game();
};