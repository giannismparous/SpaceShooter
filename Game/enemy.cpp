#include "enemy.h"
#include "graphics.h"
#include "config.h"

void enemy::update()
{	
	if (moveX==pos_x && moveY==pos_y){
			srand(graphics::getGlobalTime());
			moveX = (rand() % CANVAS_WIDTH/10)*10;
			moveY = (rand() % CANVAS_HEIGHT/10)*10;
	}
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
}

void enemy::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "enemy.png";
	br.outline_opacity = 0.0f;

	graphics::setOrientation(rotation);
	graphics::drawRect(pos_x, pos_y, size, size, br);
	br.texture = "";
	br.fill_opacity = 0.0f;
	graphics::drawDisk(pos_x, pos_y, radius, br);
	graphics::resetPose();
}

void enemy::init()
{
	moveX = (rand() % CANVAS_WIDTH / 10) * 10 ;
	moveY = (rand() % CANVAS_HEIGHT / 10) * 10;
}


enemy::enemy()
{
	init();
}

enemy::~enemy()
{
}
