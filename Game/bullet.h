#pragma once
#include "GameObject.h"
#include "graphics.h"
#include "config.h"
#include <iostream>


class bullet : public GameObject
{
	float pos_x, pos_y;
	float speed = 8.f;
	float anglee;
	float size=30;
	float radius = size - 25;
	float length;
	bool mode;
public:
	void update() override;
	void draw() override;
	void init() override;
	bullet();
	~bullet();
	void setPos_x(float px) { pos_x = px; }
	void setPos_y(float py) { pos_y = py; }
	void set_Ang(float an) { 
		anglee = an;
		//std::cout<<"Angle made:" << anglee << std::endl;
	}
	float getRadius() { return radius; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	bool isActive() {
		if (pos_x<0 || pos_x>CANVAS_WIDTH || pos_y <0 || pos_y>CANVAS_HEIGHT)return false;
		return true;
	}
	void set_mode(bool m) { mode = m; }
};