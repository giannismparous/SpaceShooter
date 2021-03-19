#pragma once

#include <cmath>

class GameObject
{
public:
	GameObject() {};
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};
