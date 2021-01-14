#pragma once
#include "enemy2.h"

class enemy4 : public enemy2
{
    float spin;
    float angle;
    bool multiplied;
public:
    enemy4(bool multiplied,float initialX=0, float initialY=0, float angle = 0) {
        this->multiplied = multiplied;
        size = multiplied ? 50 : 80;
        radius = size/2.5;
        spin = 145 / (multiplied ? 3 : 4);
        if (multiplied) { 
            this->angle = angle;
            setPosX(initialX);
            setPosY(initialY);
        }
    }
    void setAngle(float angle) { this->angle = angle; }
    virtual void update() override;
    virtual void draw() override;
    virtual bool getMultiplied() override { return multiplied; }
    virtual bool getTransformState() override { return true; }
};