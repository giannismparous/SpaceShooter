#pragma once
#include "vector"
#include "Player.h"
#include "enemy.h"
#include "enemy2.h"
#include "enemy3.h"
#include "enemy4.h"
#include "bullet.h"
#include "powerup.h"
#include "meteorite.h"




class Game
{
    char playerCoords[40];
    char enemiesAlive[5];
    char playerScore[40];
    graphics::Brush br;
    bool startMenuInitialized = false;;
    bool debugMode = false;
    bool aliveState = true;
    bool stateGame = false;
    bool shouldFire = true;
    bool spawnMeteorite = true;;
    int spaceshipPos=2;
    int lastTime;
    int reloadTimer;
    int cooldown;
    int cooldown2;
    int cooldown3;
    int cooldown4;
    int spawnedPowerupCooldown;
    int activatedPowerupCooldown;
    int enemyCounter;
    int enemyCounter2;
    int enemyCounter3;
    int enemyCounter4;
    int powerupCounter;
    int score;
    int starttimer;
    int CountBullets = 0;
    int i=0;
    int j=0; 
    int k = 0;
    bool player_initialized = false;
    bool MenuFlash = true;
    float deathX;
    float deathY;
    float lastTimeEnemy;
    float lastTimeEnemy2;
    float lastTimeEnemy3;
    float lastTimeEnemy4;
    float lastTimeSpawnedPowerup;
    float lastTimeActivatedPowerupCooldown;
    float replayTime=0;
    Player* player = nullptr;
    powerup* power = nullptr;
    std::vector<meteorite*>meteorites;
    std::vector<Player*>tempPlayers;
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
    void startMenuInit();
    void init();
    void spawnEnemies();
    void spawnMeteorites();
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