#pragma once

#include <cmath>

class GameObject
{
	static float playerX;
	static float playerY;
public:
	GameObject();
	static void setPlayerX(float x) { playerX = round(x); }
	static void setPlayerY(float y) { playerY = round(y); }
	float getPlayerX() { return playerX; }
	float getPlayerY() { return playerY; }
	virtual void update() = 0;
	virtual void draw()= 0;
	virtual void init() = 0;

};
