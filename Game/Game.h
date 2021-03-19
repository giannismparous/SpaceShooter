#pragma once
#include "vector"
#include "Player.h"
#include "enemy.h"
#include "enemy2.h"
#include "enemy3.h"
#include "enemy4.h"
#include "boss.h"
#include "bullet.h"
#include "powerup.h"




class Game
{
    typedef enum {startMenu,gamePlay} status;
    char playerScore[40];
    const int enemiesTilBoss=30;
    int spaceshipPos=2;
    int lastTime;
    int reloadTimer;
    int cooldown;
    int cooldown2;
    int cooldown3;
    int cooldown4;
    int spawnedPowerupCooldown= 15000;
    int activatedPowerupCooldown=10000;
    int phaseOneCooldown=700;
    int phaseTwoCooldown=500;
    int enemyCounter;
    int enemyCounter2;
    int enemyCounter3;
    int enemyCounter4;
    int enemiesKilled;
    int enemiesSpawned;
    int phaseTwoShots;
    int powerupCounter;
    int score;
    int starttimer;
    int CountBullets;
    int i;
    int j;
    float deathX;
    float deathY;
    float lastTimeEnemy;
    float lastTimeEnemy2;
    float lastTimeEnemy3;
    float lastTimeEnemy4;
    float lastTimeSpawnedPowerup;
    float lastTimeActivatedPowerup;
    float lastTimeShotPhaseOne;
    float lastTimeShotPhaseTwo;
    float replayTime;
    bool startMenuInitialized = false;
    bool shouldFire = true;
    bool player_initialized = false;
    bool MenuFlash = true;
    bool spawnedBossMinions;
    graphics::Brush br;
    graphics::Brush shieldBr;
    graphics::MouseState mouse;
    status gameState = startMenu;
    Player* player = nullptr;
    powerup* power = nullptr;
    boss* finalBoss = nullptr;
    std::vector<Player*>tempPlayers;
    std::vector<bullet*> bullets;
    std::vector<enemy*> enemies;
    std::vector<enemy2*> enemies2;
    std::vector<bullet*> enemyBullets;
public:
    void update();
    void StartMenu();
    void startMenuInit();
    void GameUpdate();
    void spawnPlayer();
    void updateGameObjects();
    void checkPlayerFire();
    void spawnEnemies();
    void spawnFinalBoss();
    void checkFinalBossFire();
    void CheckCollision();
    void killPlayer();
    void restart();
    void draw();
    void StartMenuDraw();
    void GameUpdateDraw();
    void drawGameObjects();
    void init();
    void playerFire();
    void playerFireTriple();
    void enemyFire(int i);
    void enemyFireTriple(int i);
    void bossFireTriple();
    void bossFireUlti();
    void spawnBossMinions();
    Game();
    ~Game();
};