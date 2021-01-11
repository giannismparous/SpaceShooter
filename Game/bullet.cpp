#include "bullet.h"
#include <iostream>

void bullet::update()
{
		pos_x -= sin(anglee*PI/180)*speed * graphics::getDeltaTime() / 10.0f;
		pos_y -= cos(anglee * PI / 180) * speed * graphics::getDeltaTime() / 10.0f;

	//std::cout << "Bullet moved to " << pos_x << "," << pos_y << std::endl;
}

void bullet::draw()
{

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	graphics::setOrientation(anglee);
	br.texture = std::string(ASSET_PATH) + "bullet.png";
	if (mode)
	{
		br.fill_color[0] = { 0.f };
		br.fill_color[1] = { 128.f };
		br.fill_color[2] = { 256.f };
	}
	else
	{
		br.fill_color[0] = { 255.f };
		br.fill_color[1] = { 0.f };
		br.fill_color[2] = { 0.f };
	}
	graphics::drawRect(pos_x, pos_y, size/2,size , br);
	br.texture = "";
	br.fill_opacity = 0.0f;
	graphics::drawDisk(pos_x, pos_y, radius, br);
	graphics::resetPose();
	graphics::resetPose();

}

void bullet::init()
{
}

bullet::bullet()
{
}

bullet::~bullet()
{
}
