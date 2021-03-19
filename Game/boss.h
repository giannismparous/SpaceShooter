#pragma once
#include "enemies.h"
#include "graphics.h"
#include <random>
#include "config.h"

class boss : public enemies
{
    float pos_x, pos_y;
    float rotation;
    float lastTimeFired;
    bool active = true;
    int moveX;
    int moveY;
    int changedLocation=1;
    int lastTimeMoved;
    int stay = 5000;
    int lives;
    const int maxHP=100;
    float speed = 3.f;
    float size = 90.f;
    float radius = size / 2;
public:
    void update() override;
    void draw() override;
    void init() override;
    void hit() { if (lives > 0)lives--; }
    int getChangedLocation() { return changedLocation; }
    bool isAtPlace() { return (pos_x == moveX && pos_y == moveY); }
    bool isAlive() { return lives > 0; }
    float getPosX() { return pos_x; }
    float getPosY() { return pos_y; }
    float getRadius() { return radius; }
    float getRotation() { return rotation; }
    int getLives() { return lives; }
    int getMaxHP() { return maxHP; }
    boss() {
        srand(graphics::getGlobalTime() + 32 * rand() % 5);
        if (getPlayerX() < CANVAS_WIDTH / 2)pos_x = rand() % CANVAS_WIDTH / 2 + CANVAS_WIDTH / 2;
        else if (getPlayerX() > CANVAS_WIDTH / 2)pos_x = rand() % CANVAS_WIDTH / 2;
        else {
            if (rand() % 2 == 0)pos_x = CANVAS_WIDTH - rand() % CANVAS_WIDTH / 8;
            else pos_x = rand() % CANVAS_WIDTH / 8;
        }
        if (getPlayerY() < CANVAS_HEIGHT / 2)pos_y = rand() % CANVAS_HEIGHT / 2 + CANVAS_HEIGHT / 2;
        else if (getPlayerY() > CANVAS_HEIGHT / 2)pos_y = rand() % CANVAS_HEIGHT / 2;
        else {
            if (rand() % 2 == 0)pos_y = CANVAS_HEIGHT - rand() % CANVAS_HEIGHT / 8;
            else pos_y = rand() % CANVAS_HEIGHT / 8;
        }
        moveX = (rand() % CANVAS_WIDTH / 10) * 10;
        moveY = (rand() % CANVAS_HEIGHT / 10) * 10;
        lastTimeMoved = graphics::getGlobalTime();
        lives = maxHP;
    }
};