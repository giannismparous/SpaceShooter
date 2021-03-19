#pragma once
#include "enemies.h"
#include "graphics.h"
#include <random>
#include "config.h"

class enemy2 : public enemies
{
    float pos_x, pos_y;
    float rotation;
    bool active = true;
    float speed = 5.f;
protected:
    float size = 50.f;
    float radius = size / 2;
public:
    virtual void update() override;
    virtual void draw() override;
    void init() override;
    bool isActive() { return active; }
    void setInactive() { active = false; }
    void setXY() {
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
    }
    void setXY(float x, float y) {
        pos_x = x;
        pos_y = y;
    }
    void setPosX(float pos_x) { this->pos_x = pos_x; }
    void setPosY(float pos_y) { this->pos_y = pos_y; }
    float getPosX() { return pos_x; }
    float getPosY() { return pos_y; }
    float getRadius() { return radius; }
    float getRotation() { return rotation; }
    virtual bool getMultiplied() { return false; }
    virtual bool getTransformState() { return false; }
    enemy2() ;
    ~enemy2();
};