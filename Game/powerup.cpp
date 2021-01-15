#include "powerup.h"

void powerup::update()
{
}

void powerup::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	if (type == 0) br.texture = std::string(ASSET_PATH) + "shield.png";
	else if (type == 1) br.texture = std::string(ASSET_PATH) + "multishot.png";
	else if (type == 2) br.texture = std::string(ASSET_PATH) + "pierce.png";
	else if (type == 3) br.texture = std::string(ASSET_PATH) + "heartPowerup.png";
	graphics::drawRect(posX,posY,size,size,br);
	br.texture = "";
	br.fill_opacity = 0.0f;
	graphics::drawDisk(posX, posY, radius, br);
}

void powerup::init()
{
}

powerup::powerup()
{
}

powerup::~powerup()
{
}
