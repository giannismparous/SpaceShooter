#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"

class Player
{	
	int lives;
	float speed = 8.0f;
	float pos_x=CANVAS_WIDTH/2, pos_y=CANVAS_HEIGHT/2;
	float size = 80;
	float heartSize = 30;
	float radius = size / 3 + 9;
	float anglee;
	graphics::MouseState mouse;

public:
	Player();
	void update();
	void draw();
	void init();
	void hit()
	{ 
		lives -= 1;
		if (lives == 0)
		{
		graphics::playSound(std::string(ASSET_PATH) + "rip.mp3", 0.8f);
		}
		else
		{
		graphics::playSound(std::string(ASSET_PATH) + "death.mp3", 0.20f);
		}
	}
	int getLives() { return lives; }
	float getRadius() { return radius; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	float getAng() { return anglee; }
};