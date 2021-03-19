#pragma once 
#include "GameObject.h"

class enemies :public GameObject
{
	static float playerX;
	static float playerY;
public:
	enemies();
	static void setPlayerX(float x) { playerX = round(x); }
	static void setPlayerY(float y) { playerY = round(y); }
	float getPlayerX() { return playerX; }
	float getPlayerY() { return playerY; }
	void update() = 0;
	void draw() = 0;
	void init() = 0;
};