#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"

class Player
{	
	int lives=3;
	bool alive = true;
	float speed = 8.0f;
	float pos_x=CANVAS_WIDTH/2, pos_y=CANVAS_HEIGHT/2;
	float size = 80;
	float heartSize = 30;
	float radius = size / 3 + 9;
	float anglee;

public:
	Player();
	void update();
	void draw();
	void init();
	void hit(){ lives -= 1; }
	int getLives() { return lives; }
	float getRadius() { return radius; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	float getAng() { return anglee; }
};