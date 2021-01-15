#pragma once

#include "GameObject.h"
#include "graphics.h"
#include "config.h"

class powerup : public GameObject {
	int type=-1;
	int size=0;
	float radius=0;
	float posX, posY;
public:
	virtual void update() override;
	virtual void draw() override;
	virtual void init() override;
	int getType() { return type; }
	void setType(int t) { 
		type = t;
		if (type == 0) {
			size = 40;
			radius = size / 1.65;
		}
		else if (type == 1) {
			size = 40;
			radius = size / 1.7;
		}
		else if (type == 2) {
			size = 65;
			radius = size / 2.35;
		}
		else if (type == 3) {
			size = 40;
			radius = size / 1.7;
		}
		else { size = 0; radius = 0; }
	}
	void setPosX(float x) { posX = x; }
	void setPosY(float y) { posY = y; }
	int getPosX() { return posX; }
	int getPosY() { return posY; }
	float getRadius() { return radius; }
	powerup();
	~powerup();
};