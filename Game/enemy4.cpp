#include "enemy4.h"

void enemy4::update() {
	if (!multiplied) { 
		enemy2::update();
		spin += 1.5*graphics::getDeltaTime();
		spin = fmod(spin, 360);
	}
	else
	{
		int rotationForMovement = -(getRotation()+angle);
		rotationForMovement = fmodf(rotationForMovement, 360);
		setPosX(getPosX()-sin(rotationForMovement * PI / 180) *3* graphics::getDeltaTime() / 10.0f);
		setPosY(getPosY()-cos(rotationForMovement * PI / 180)*3* graphics::getDeltaTime() / 10.0f);
		if (getPosX() > CANVAS_WIDTH || getPosX() < 0 || getPosY() > CANVAS_HEIGHT || getPosY() < 0)setInactive();
		spin += 0.5 * graphics::getDeltaTime();
		spin = fmod(spin, 360);
	}
}

void enemy4::draw() {

	graphics::Brush br;
	if (!multiplied) br.texture = std::string(ASSET_PATH) + "enemy4a.png";
	else br.texture = std::string(ASSET_PATH) + "enemy4b.png";
	br.outline_opacity = 0.0f;
	graphics::setOrientation(spin);
	graphics::drawRect(getPosX(), getPosY(), size, size, br);
	br.texture = "";
	br.fill_opacity = 0.0f;
	graphics::drawDisk(getPosX(), getPosY(), radius, br);
	graphics::resetPose();
	
}