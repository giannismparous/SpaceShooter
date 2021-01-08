#pragma once
#include "GameObject.h"
#include "graphics.h"
#include <random>
#include "config.h"
#include <iostream>

class enemy : public GameObject
{
    float pos_x, pos_y;
    float speed = 2.f;
    float size = 50.f;
    float radius = size / 3;
    float rotation;
    float lastTimeFired;
    bool active = true;
    graphics::Brush brush;
    int moveX;
    int moveY;
public:
    void update() override;
    void draw() override;
    void init() override;
    bool isActive() { return active; }
    void setInactive() { active = false; }
    void setLastTimeFired(int newTime) { lastTimeFired = newTime; }
    void setXY() {
        srand(graphics::getGlobalTime() + 32 * rand() % 5);
        if (getPlayerX() < CANVAS_WIDTH/2)pos_x = rand() % CANVAS_WIDTH/2 + CANVAS_WIDTH/2;
        else if (getPlayerX() > CANVAS_WIDTH/2)pos_x = rand() % CANVAS_WIDTH/2;
        else {
            if (rand() % 2 == 0)pos_x = CANVAS_WIDTH - rand()% CANVAS_WIDTH / 8;
            else pos_x = rand() % CANVAS_WIDTH / 8;
        }
        if (getPlayerY() < CANVAS_HEIGHT/2)pos_y = rand() % CANVAS_HEIGHT/2 + CANVAS_HEIGHT/2;
        else if (getPlayerY() > CANVAS_HEIGHT/2)pos_y = rand() % CANVAS_HEIGHT/2;
        else {
            if (rand() % 2 == 0)pos_y = CANVAS_HEIGHT - rand() % CANVAS_HEIGHT / 8;
            else pos_y = rand() % CANVAS_HEIGHT / 8;
        }
        //std::cout << abs(getPlayerX() - pos_x) << " " << abs(getPlayerY() - pos_y) << std::endl;
    }
    float getRadius() { return radius; }
    float getPosX() { return pos_x; }
    float getPosY() { return pos_y; }
    float getRotation() { return rotation; }
    float getLastTimeFired() { return lastTimeFired; }
    enemy();
    ~enemy();
};