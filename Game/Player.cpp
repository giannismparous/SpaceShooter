#include "Player.h"
#include "graphics.h"
#include "math.h"
#include <cmath>
#include <iostream>

Player::Player()
{
	lives = 3;
}

void Player::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		pos_x -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		pos_y += speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_W))
	{
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH)  pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT)  pos_y = CANVAS_HEIGHT;

	graphics::getMouseState(mouse);
	anglee = -(atan2((graphics::windowToCanvasY(mouse.cur_pos_y) - pos_y) , (graphics::windowToCanvasX(mouse.cur_pos_x) - pos_x))*180/PI)-90.f;
	anglee = fmodf(anglee, 360);
}

void Player::draw()
{
	graphics::Brush br;
	if (lives > 3)lives = 3;
	for (int j = 0; j < lives; j++) {
		br.texture = std::string(ASSET_PATH) + "heart.png";
		br.outline_opacity = 0.0f;
		//std::cout << lives << std::endl;
		graphics::drawRect((j+1)*CANVAS_WIDTH/40, CANVAS_HEIGHT-50, heartSize+heartSize/2, heartSize, br);
	}

	br.texture = std::string(ASSET_PATH) + "spaceship.png";
	br.outline_opacity = 0.0f;
	
	graphics::setOrientation(anglee);
	graphics::drawRect(pos_x, pos_y, size, size, br);
	br.texture = "";
	br.fill_opacity = 0.0f;
	graphics::drawDisk(pos_x, pos_y, radius, br);
	graphics::resetPose();
	
}

void Player::init()
{
}