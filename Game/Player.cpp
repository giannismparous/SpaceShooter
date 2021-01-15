#include "Player.h"
#include "graphics.h"
#include "math.h"
#include <cmath>
#include <iostream>

void Player::update()
{
	if (!automated) {
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
	}
	graphics::getMouseState(mouse);
	anglee = -(atan2((graphics::windowToCanvasY(mouse.cur_pos_y) - pos_y) , (graphics::windowToCanvasX(mouse.cur_pos_x) - pos_x))*180/PI)-90.f;
	anglee = fmodf(anglee, 360);
}

void Player::draw()
{
	graphics::Brush br;
	if (lives > 4)lives = 4;
	for (int j = 0; j < lives; j++) {
		br.texture = std::string(ASSET_PATH) + "heart.png";
		br.outline_opacity = 0.0f;
		//std::cout << lives << std::endl;
		graphics::drawRect((j+1)*CANVAS_WIDTH/40, CANVAS_HEIGHT-50, heartSize+heartSize/2, heartSize, br);
	}
	graphics::setOrientation(anglee);
	if (spaceshipType==1)br.texture = std::string(ASSET_PATH) + "spaceship1.png";
	else if  (spaceshipType == 2)br.texture = std::string(ASSET_PATH) + "spaceship2.png";
	else if (spaceshipType == 3)br.texture = std::string(ASSET_PATH) + "spaceship3.png";
	if (selected) {
		graphics::Brush shadowBr;
		shadowBr.outline_opacity = 0.0f;
		shadowBr.gradient = true;
		shadowBr.fill_color[0] = 0.0f;
		shadowBr.fill_color[1] = 0.0f;
		shadowBr.fill_color[2] = 1.0f;
		shadowBr.fill_secondary_color[0] = 1.0f;
		shadowBr.fill_secondary_color[1] = 0.0f;
		shadowBr.fill_secondary_color[2] = 0.0f;
		shadowBr.fill_opacity = 0.85f;
		shadowBr.fill_secondary_opacity = 0.75f;
		shadowBr.texture = br.texture;
		graphics::drawRect(pos_x, CANVAS_HEIGHT / 2 + 200, size + 40, (spaceshipType == 3) ? size + 50 : size + 40, shadowBr);
	}
	else if (!selected && automated)br.fill_opacity = 0.3;
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, (spaceshipType==3)?size+10:size , br);
	br.texture = "";
	br.fill_opacity = 0.0f;
	graphics::drawDisk(pos_x, pos_y, radius, br);
	graphics::resetPose();
	
}

void Player::init()
{
}