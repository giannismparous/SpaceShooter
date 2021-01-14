#pragma once
#include "vector"
#include "Player.h"
#include "enemy.h"
#include "enemy2.h"
#include "enemy3.h"
#include "enemy4.h"
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
    int reloadTimer;
    int cooldown;
    int cooldown2;
    int cooldown3;
    int cooldown4;
    int enemyCounter;
    int enemyCounter2;
    int enemyCounter3;
    int enemyCounter4;
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
    float lastTimeEnemy3;
    float lastTimeEnemy4;
    float replayTime=0;
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
    void init();
    void spawnEnemies();
    void CheckCollision();
    void enemyFire(int i);
    void enemy2Fire(int i);
    void StartMenu();
    void GameUpdate();
    void StartMenuDraw();
    void GameUpdateDraw();
    Game();
    ~Game();
};