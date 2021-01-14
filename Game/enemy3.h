#pragma once
#include "enemy.h"

class enemy3 : public enemy
{
public:
    virtual void draw() override;
    virtual bool getTransformState() override { return true; }
    enemy3() {
        size = 50.f;
        radius = size/2;
    }
};