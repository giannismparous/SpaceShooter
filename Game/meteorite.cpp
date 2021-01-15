#include "meteorite.h"

void meteorite::update()
{
	pos_x -= sin(movementAngle * PI / 180) * speed * graphics::getDeltaTime() / 10.0f;
	pos_y -= cos(movementAngle * PI / 180) * speed * graphics::getDeltaTime() / 10.0f;
	spin += velocity/200 * graphics::getDeltaTime();
	spin = fmod(spin, 360);
}

void meteorite::draw()
{
	graphics::Brush br;
	if (type == 0)br.texture = std::string(ASSET_PATH) + "meteorite1.png";
	else br.texture = std::string(ASSET_PATH) + "meteorite2.png";
	br.outline_opacity = 0.0f;
	graphics::setOrientation(spin);
	graphics::drawRect(pos_x, pos_y, size, size, br);
	graphics::resetPose();
}

void meteorite::init()
{
}
