#include "enemy3.h"

void enemy3::draw() {

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "enemy3.png";
	br.outline_opacity = 0.0f;
	graphics::setOrientation(getRotation());
	graphics::drawRect(getPosX(), getPosY(), size, size, br);
	br.texture = "";
	br.fill_opacity = 0.0f;
	graphics::drawDisk(getPosX(), getPosY(), radius, br);
	graphics::resetPose();

}