#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"
#include "math.h"
#include <random>

class meteorite: public GameObject {
    float initialX, initialY;
    float pos_x, pos_y;
    float moveX, moveY;
    float speed=3;
    float movementAngle;
    float spin,velocity;
    float size;
    int type;
    float borderX, borderY;
public:
    void update() override;
    void draw() override;
    void init() override;
    bool isActive() {
        if (initialX < CANVAS_WIDTH / 2 && pos_x >= CANVAS_WIDTH)return false;
        else if (initialX > CANVAS_WIDTH / 2 && pos_x <= 0)return false;
        if (initialY < CANVAS_HEIGHT / 2 && pos_y >= CANVAS_HEIGHT)return false;
        else if (initialY > CANVAS_HEIGHT / 2 && pos_y <= 0)return false;
        return true;
    }
    meteorite() {
        for (int i = 0; i < rand() % 3;i++) srand(graphics::getGlobalTime() * graphics::getDeltaTime());
        if (rand() % 2 == 0)moveX = CANVAS_WIDTH/2+rand()%(CANVAS_WIDTH/4);
        else moveX = CANVAS_WIDTH - rand() % (CANVAS_WIDTH / 4);
        if (rand() % 2 == 0)moveY = CANVAS_HEIGHT / 2 + rand() % (CANVAS_HEIGHT / 4);
        else moveY = CANVAS_HEIGHT - rand() % (CANVAS_HEIGHT / 4);
        if (rand() % 2 == 0)pos_x = -(rand() % (CANVAS_WIDTH / 3));
        else pos_x = CANVAS_WIDTH+rand()%(CANVAS_WIDTH/3);
        if (rand() % 2 == 0)pos_y = -(rand() % (CANVAS_HEIGHT / 3));
        else pos_y = CANVAS_HEIGHT + rand() % (CANVAS_HEIGHT / 3);
        initialX = pos_x;
        initialY = pos_y;
        borderX = (abs(pos_x - 0) > abs(pos_x - CANVAS_WIDTH) ? 0 : CANVAS_WIDTH);//
        borderY = (abs(pos_y - 0) > abs(pos_y - CANVAS_HEIGHT) ? 0 : CANVAS_HEIGHT);
        movementAngle = -(atan2(moveY - pos_y, moveX - pos_x) * 180 / PI) - 90.f;
        movementAngle = fmodf(movementAngle, 360);
        velocity = rand() % 100;
        type = rand() % 2;
        size = 30 +rand()%10;
    }
};