#include "boss.h"

void boss::update()
{
	if (abs(pos_x - moveX) > 2) {
		if (moveX < pos_x)pos_x -= round(speed * graphics::getDeltaTime() / 10.0f);
		else if (moveX > pos_x)pos_x += round(speed * graphics::getDeltaTime() / 10.0f);
	}
	else pos_x = moveX;
	if (abs(pos_y - moveY) > 2) {
		if (moveY < pos_y)pos_y -= round(speed * graphics::getDeltaTime() / 10.0f);
		else if (moveY > pos_y)pos_y += round(speed * graphics::getDeltaTime() / 10.0f);
	}
	else pos_y = moveY;
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH)  pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT)  pos_y = CANVAS_HEIGHT;
	rotation = -(atan2((getPlayerY() - pos_y), (getPlayerX() - pos_x)) * 180 / PI) - 90.f;
	rotation = fmodf(rotation, 360);

	if (moveX == pos_x && moveY == pos_y && graphics::getGlobalTime()-lastTimeMoved>stay) {
		changedLocation++;
		if (changedLocation % 5 == 0) {
			moveX = CANVAS_WIDTH / 2;
			moveY = CANVAS_HEIGHT / 2;
			stay = 10000;
		}
		else {
			srand(graphics::getGlobalTime());
			moveX = (rand() % CANVAS_WIDTH / 10) * 10;
			moveY = (rand() % CANVAS_HEIGHT / 10) * 10;
			stay = 5000;
		}
		lastTimeMoved = graphics::getGlobalTime();
	}
}

void boss::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "boss.png";
	br.outline_opacity = 0.0f;
	graphics::setOrientation(rotation);
	graphics::drawRect(pos_x, pos_y, size + size / 2, size+size/2, br);
	br.texture = "";
	br.fill_opacity = 0.0f;
	graphics::drawDisk(pos_x, pos_y, radius, br);
	graphics::resetPose();
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.fill_secondary_color[0] = 0.2f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	br.outline_opacity = 1.0f;
	graphics::drawRect(CANVAS_WIDTH/2, CANVAS_HEIGHT - 30, 15 * lives, 20, br);
}

void boss::init()
{
}
