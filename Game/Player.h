#pragma once
#include "GameObject.h"
#include "config.h"
#include "graphics.h"

class Player:public GameObject
{
	int lives = 3;
	int powerupType = -1;
	int spaceshipType=2;
	float speed = 8.0f;
	float pos_x,pos_y;
	float size;
	float radius;
	float heartSize = CANVAS_WIDTH / 53.3;
	float angle;
	bool automated;
	bool selected=false;
	graphics::MouseState mouse;

public:
	Player(float initialX = CANVAS_WIDTH / 2, float initialY = CANVAS_HEIGHT / 2, bool initialAutomated=false) {
		pos_x = initialX;
		pos_y = initialY;
		automated = initialAutomated;
	}
	void update();
	void draw();
	void init();
	void hit()
	{
		if (lives>0)lives -= 1;
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
	float getSize() { return size; }
	float getAng() { return angle; }
	int getPowerupType() { return powerupType; }
	void setPowerupType(int powerupType) {
		if (powerupType == 3) lives++;
		this->powerupType = powerupType;
	}
	void setSpaceshipType(int spaceshipType) {
		if (spaceshipType == 1) {
			size = 70;
			radius = size / 2.1;
		}
		else if (spaceshipType == 2) {
			size = 80;
			radius = size / 2.9;
		}
		else if (spaceshipType == 3) {
			size = 90;
			radius = size / 2.85;
		}
		this->spaceshipType = spaceshipType;
	}
	void setSelected(bool selection) { selected = selection; }

};