#include "Player.h"
#include "graphics.h"

void Player::update()
{
	if (!automated) {
		if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT))
		{
			pos_x -= speed * graphics::getDeltaTime() / 10.0f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT))
		{
			pos_x += speed * graphics::getDeltaTime() / 10.0f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_S) || graphics::getKeyState(graphics::SCANCODE_DOWN))
		{
			pos_y += speed * graphics::getDeltaTime() / 10.0f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_W) || graphics::getKeyState(graphics::SCANCODE_UP))
		{
			pos_y -= speed * graphics::getDeltaTime() / 10.0f;
		}
		if (pos_x < 0) pos_x = 0;
		if (pos_x > CANVAS_WIDTH)  pos_x = CANVAS_WIDTH;
		if (pos_y < 0) pos_y = 0;
		if (pos_y > CANVAS_HEIGHT)  pos_y = CANVAS_HEIGHT;
	}
	graphics::getMouseState(mouse);
	angle = -(atan2((graphics::windowToCanvasY(mouse.cur_pos_y) - pos_y) , (graphics::windowToCanvasX(mouse.cur_pos_x) - pos_x))*180/PI)-90.f;
	angle = fmodf(angle, 360);

	if (lives > 4)lives = 4;
}

void Player::draw()
{
	graphics::Brush br;
	if (!automated) {
		br.texture = std::string(ASSET_PATH) + "heart.png";
		br.outline_opacity = 0.0f;
		for (int j = 0; j < lives; j++) {
			graphics::drawRect((j + 1) * CANVAS_WIDTH / 40, 85, heartSize + heartSize / 2, heartSize, br);
		}
	}
	graphics::setOrientation(angle);
	if (spaceshipType==1)br.texture = std::string(ASSET_PATH) + "spaceship1.png";
	else if  (spaceshipType == 2)br.texture = std::string(ASSET_PATH) + "spaceship2.png";
	else if (spaceshipType == 3)br.texture = std::string(ASSET_PATH) + "spaceship3.png";
	if (!selected && automated)br.fill_opacity = 0.3;
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, (spaceshipType==3)?size+10:size , br);
	br.fill_opacity = 0.0f;
	graphics::drawDisk(pos_x, pos_y, radius, br);
	graphics::resetPose();
	
}

void Player::init()
{
}