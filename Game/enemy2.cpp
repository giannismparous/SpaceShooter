#include "enemy2.h"
#include "config.h"

void enemy2::update()
{
	rotation = -(atan2((getPlayerY() - pos_y), (getPlayerX() - pos_x)) * 180 / PI) - 90.f;
	rotation = fmodf(rotation, 360);
	if (abs(pos_x - getPlayerX()) > 2) {
		pos_x -= sin(rotation * PI / 180) * speed * graphics::getDeltaTime() / 10.0f;
	}
	else pos_x = getPlayerX();
	if (abs(pos_y - getPlayerY()) > 2) {
		pos_y -= cos(rotation * PI / 180) * speed * graphics::getDeltaTime() / 10.0f;
	}
	else pos_y = getPlayerY();
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH)  pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT)  pos_y = CANVAS_HEIGHT;
	
}

void enemy2::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "enemy2.png";
	br.outline_opacity = 0.0f;

	graphics::setOrientation(rotation);
	graphics::drawRect(pos_x, pos_y, size+size/2, size+size/2, br);
	br.texture = "";
	br.fill_opacity = 0.0f;
	graphics::drawDisk(pos_x, pos_y, radius, br);
	graphics::resetPose();
}

void enemy2::init()
{
}


enemy2::enemy2()
{
}

enemy2::~enemy2()
{
}
