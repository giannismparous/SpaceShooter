#include "Game.h"
#include "graphics.h"
#include "config.h"
#include <iostream>

void Game::StartMenu()
{
	if (graphics::getKeyState(graphics::SCANCODE_T))
	{
		stateGame = true;
	}
}

void Game::GameUpdate()
{
	if (!player_initialized)
	{
		player = new Player();
		player_initialized = true;
		lastTime = graphics::getGlobalTime() - 3500;
		lastTimeEnemy = graphics::getGlobalTime();
		lastTimeEnemy2 = graphics::getGlobalTime();
		lastTimeEnemy3 = graphics::getGlobalTime();
		lastTimeEnemy4 = graphics::getGlobalTime();
		//std::cout << lastTime << " " << graphics::getGlobalTime() << std::endl;
		cooldown = 2000;
		cooldown2 = 3000;
		cooldown3 = 7000;
		cooldown4 = 8000;
		enemyCounter = 0;
		enemyCounter2 = 0;
		enemyCounter3 = 0;
		enemyCounter4 = 0;
		score = 0;
		i = 0;
		j = 0;
		CountBullets = 0;
		reloadTimer = graphics::getGlobalTime();
	}
	if (player && getAliveState()) {
		player->update();
		if (graphics::getKeyState(graphics::SCANCODE_F))debugMode = !debugMode;
	}

	graphics::getMouseState(mouse);


	if (mouse.button_left_pressed && getAliveState() && shouldFire)
	{

		bullets.push_back(new bullet());
		bullets.back()->setPos_x(player->getPosX());
		bullets.back()->setPos_y(player->getPosY());
		bullets.back()->set_Ang(player->getAng());
		bullets.back()->set_mode(true);
		CountBullets++;
		if (CountBullets >= 8)
		{
			graphics::playSound(std::string(ASSET_PATH) + "lastfire.ogg", 0.5f);
		}
		else
		{
			graphics::playSound(std::string(ASSET_PATH) + "primaryfire.ogg", 0.5f);
		}
		//std::cout << "Mouse clicked at:" << mouse.cur_pos_x << "," << mouse.cur_pos_y << std::endl;
		//std::cout << "Player coords:" << player->getPosX() << "," << player->getPosY() << std::endl;
	}

	if (graphics::getGlobalTime() - reloadTimer > 2500 && getAliveState())
	{
		if (CountBullets >0)CountBullets--;
		reloadTimer = graphics::getGlobalTime();
	}
	

	if (CountBullets >= 8) {
		shouldFire = false;
		lastTime = graphics::getGlobalTime();
		CountBullets = 0;
	}

	if  (graphics::getGlobalTime() - lastTime > 3500) {
		shouldFire = true;
	}

	while (i < bullets.size()) {
		if (bullets[i]->isActive())bullets[i]->update();
		else {
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			continue;
		}
		i++;
	}

	i = 0;

	while (i < enemyBullets.size()) {
		if (enemyBullets[i]->isActive())enemyBullets[i]->update();
		else {
			delete enemyBullets[i];
			enemyBullets.erase(enemyBullets.begin() + i);
			continue;
		}
		i++;
	}

	i = 0;

	if (bullets.size() >= 8) { lastTime = graphics::getGlobalTime();  }


	GameObject::setPlayerX(player && getAliveState() ? player->getPosX() : deathX);
	GameObject::setPlayerY(player && getAliveState() ? player->getPosY() : deathY);

	spawnEnemies();

	while (i < enemies.size()) {
		enemies[i]->update();
		srand(graphics::getGlobalTime() + rand());
		if (graphics::getGlobalTime() - enemies[i]->getLastTimeFired() > 3000 + rand() % 100000 && getAliveState() && graphics::getGlobalTime() > 3000 && enemies[i]->getTransformState()) {
			enemy2Fire(i);
			enemies[i]->setLastTimeFired(graphics::getGlobalTime());
		}
		else if (graphics::getGlobalTime() - enemies[i]->getLastTimeFired() > 2000 + rand() % 100000 && getAliveState() && graphics::getGlobalTime() > 3000 && !enemies[i]->getTransformState()) {
			enemyFire(i);
			enemies[i]->setLastTimeFired(graphics::getGlobalTime());		
		}
		i++;
	}

	i = 0;

	while (i < enemies2.size()) {
		if (enemies2[i]->isActive())enemies2[i]->update();
		else {
			delete enemies2[i];
			enemies2.erase(enemies2.begin() + i);
		}
		i++;
	}

	i = 0;

	CheckCollision();

	if (player && getAliveState() && player->getLives() <= 0) {
		kill();
		delete player;
	}
	if (!getAliveState() && graphics::getKeyState(graphics::SCANCODE_R))
	{
		player_initialized = false;
		enemies.clear();
		enemies2.clear();
		bullets.clear();
		enemyBullets.clear();
		aliveState = true;
		replayTime = graphics::getGlobalTime();
	}

	//std::cout <<"Bullets size:" << bullets.size()<<std::endl;
	//std::cout << "Enemy bullets size:" << enemyBullets.size() << std::endl;

}

void Game::StartMenuDraw()
{
	if (graphics::getGlobalTime() - starttimer > 800 ) {
		MenuFlash = !MenuFlash;
		starttimer = graphics::getGlobalTime();
	}
	if (MenuFlash) graphics::drawText(CANVAS_WIDTH / 5.5, CANVAS_HEIGHT / 2, CANVAS_WIDTH/16, "Press SPACE to Start", br);
}

void Game::GameUpdateDraw()
{
	//draw player
	if (player && getAliveState())player->draw();

	while (i < bullets.size()) {
		bullets[i]->draw();
		i++;
	}

	i = 0;

	while (i < enemies.size()) {
		enemies[i]->draw();
		i++;
	}

	i = 0;

	while (i < enemies2.size()) {
		enemies2[i]->draw();
		i++;
	}

	i = 0;

	while (i < enemyBullets.size()) {
		enemyBullets[i]->draw();
		i++;
	}

	i = 0;

	sprintf_s(playerScore, "Score:%d", score);
	graphics::drawText(20, 50, CANVAS_WIDTH/32, playerScore, br);
	//sprintf_s(playerCoords, "(%6.2f,%6.2f)", mouse.cur_pos_x, mouse.cur_pos_y);
	//graphics::drawText(30, 80, 50, playerCoords, br);
	//std::cout << mouse.cur_pos_x << " " << mouse.cur_pos_y << std::endl;

	if (debugMode && player) {
		//std::cout << enemies.back()->getPosX()<<" "<< enemies.back()->getPosY() << std::endl;
		sprintf_s(playerCoords, "(%6.2f,%6.2f)", player->getPosX(), player->getPosY());
		graphics::drawText(30, 100, 50, playerCoords, br);
		//sprintf_s(enemiesAlive,"%d", enemies.size());
		//graphics::drawText(60, 70, 50, enemiesAlive, br);
	}
	if (!getAliveState() & player_initialized)graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, CANVAS_WIDTH/22.85, "Press R to Restart", br);

	if (graphics::getGlobalTime() > 250 && graphics::getGlobalTime() - replayTime <= 250) { graphics::drawText(CANVAS_WIDTH / 3- 16*(graphics::getGlobalTime() - replayTime), CANVAS_HEIGHT / 2+ (graphics::getGlobalTime() - replayTime)*1.25, CANVAS_WIDTH/22.8+4*(graphics::getGlobalTime()-replayTime), "Press R to Restart", br); }
}

void Game::update()
{
	if (!stateGame)
	{
		StartMenu();
	}
	else
	{
		GameUpdate();
	}
}

void Game::draw()
{
	br.texture = std::string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	if (!stateGame)
	{
		StartMenuDraw();
	}
	else
	{
		GameUpdateDraw();
	}
}

void Game::spawnEnemies() {

	if (graphics::getGlobalTime() - lastTimeEnemy > cooldown) {
		enemies.push_back(new enemy());
		//std::cout <<"Enemies size:" << enemies.size()<<std::endl;
		enemies.back()->setXY();
		lastTimeEnemy = graphics::getGlobalTime();
		enemies.back()->setLastTimeFired(graphics::getGlobalTime() - 1000);
		enemyCounter++;
		if (enemyCounter / 10 != 0 && cooldown > 500) {
			enemyCounter = 0;
			cooldown -= 100;
		}
	}

	if (graphics::getGlobalTime() - lastTimeEnemy2 > cooldown2) {
		enemies2.push_back(new enemy2());
		enemies2.back()->setXY();
		lastTimeEnemy2 = graphics::getGlobalTime();
		enemyCounter2++;
		if (enemyCounter2 / 10 != 0 && cooldown2 > 500) {
			enemyCounter2 = 0;
			cooldown2 -= 100;
		}
	}

	if (graphics::getGlobalTime() - lastTimeEnemy3 > cooldown3 && score>1000) {
		enemies.push_back(new enemy3());
		//std::cout <<"Enemies size:" << enemies.size()<<std::endl;
		enemies.back()->setXY();
		lastTimeEnemy3 = graphics::getGlobalTime();
		enemies.back()->setLastTimeFired(graphics::getGlobalTime() - 1000);
		enemyCounter++;
		if (enemyCounter3 / 10 != 0 && cooldown3 > 2000) {
			enemyCounter3 = 0;
			cooldown3 -= 100;
		}
	}

	if (graphics::getGlobalTime() - lastTimeEnemy4 > cooldown4 && score>1200) {
		enemies2.push_back(new enemy4(false));
		enemies2.back()->setXY();
		lastTimeEnemy4 = graphics::getGlobalTime();
		enemyCounter4++;
		if (enemyCounter4 / 10 != 0 && cooldown4 > 2000) {
			enemyCounter4 = 0;
			cooldown4 -= 100;
		}
	}

}

void Game::CheckCollision() {
	if (player && getAliveState()) {
		while (i < enemies.size()) {
			if (sqrt(pow(player->getPosX() - enemies[i]->getPosX(), 2) + pow(player->getPosY() - enemies[i]->getPosY(), 2)) - player->getRadius() - enemies[i]->getRadius() < 0) {
				player->hit();
				if (enemies[i]->isActive()) {
					enemies[i]->setInactive();
					delete enemies[i];
					enemies.erase(enemies.begin() + i);
				}
			}
			i++;
		}
		i = 0;
	}

	if (player && getAliveState()) {
		while (i < enemies2.size()) {
			if (sqrt(pow(player->getPosX() - enemies2[i]->getPosX(), 2) + pow(player->getPosY() - enemies2[i]->getPosY(), 2)) - player->getRadius() - enemies2[i]->getRadius() < 0) {
				player->hit();
				if (enemies2[i]->isActive()) {
					enemies2[i]->setInactive();
					delete enemies2[i];
					enemies2.erase(enemies2.begin() + i);
				}
				
			}
			i++;
		}
		i = 0;
	}

	if (player && getAliveState()) {
		while (i < enemyBullets.size()) {
			if (sqrt(pow(player->getPosX() - enemyBullets[i]->getPosX(), 2) + pow(player->getPosY() - enemyBullets[i]->getPosY(), 2)) - player->getRadius() - enemyBullets[i]->getRadius() < 0) {
				player->hit();
				if (enemyBullets[i]->isActive()) {
					delete enemyBullets[i];
					enemyBullets.erase(enemyBullets.begin() + i);
				}
			}
			i++;
		}
		i = 0;
	}

	while (i < bullets.size()) {
		while (j < enemies.size()) {
			if (sqrt(pow(bullets[i]->getPosX() - enemies[j]->getPosX(), 2) + pow(bullets[i]->getPosY() - enemies[j]->getPosY(), 2)) - bullets[i]->getRadius() - enemies[j]->getRadius() < 0) {
				score += 50;
				lastTime = -3500;
				shouldFire = true;
				CountBullets = 0;
				if (bullets[i]->isActive() && enemies[j]->isActive()) {
					delete bullets[i];
					bullets.erase(bullets.begin() + i);
					delete enemies[j];
					enemies.erase(enemies.begin() + j);
					break;//OWOWOOWOWOWO
				}
			}
			j++;
		}
		j = 0;
		i++;
	}

	i = 0;

	while (i < bullets.size()) {
		while (j < enemies2.size()) {
			if (sqrt(pow(bullets[i]->getPosX() - enemies2[j]->getPosX(), 2) + pow(bullets[i]->getPosY() - enemies2[j]->getPosY(), 2)) - bullets[i]->getRadius() - enemies2[j]->getRadius() < 0) {
				score += 100;
				lastTime = -3500;
				shouldFire = true;
				CountBullets = 0;
				if (bullets[i]->isActive() && enemies2[j]->isActive()) {
					delete bullets[i];
					bullets.erase(bullets.begin() + i);
					if (enemies2[j]->getTransformState() && !enemies2[j]->getMultiplied()) {
						enemies2.push_back(new enemy4(true,enemies2[j]->getPosX(), enemies2[j]->getPosY()));
						enemies2.push_back(new enemy4(true, enemies2[j]->getPosX(), enemies2[j]->getPosY(),120));
						enemies2.push_back(new enemy4(true, enemies2[j]->getPosX(), enemies2[j]->getPosY() ,-120));
					}
					delete enemies2[j];
					enemies2.erase(enemies2.begin() + j);
					break;//OWOWOOWOWOWO
				}
			}
			j++;
		}
		j = 0;
		i++;
	}

	i = 0;
}

void Game::enemyFire(int i) {
	//std::cout << i << std::endl;
	enemyBullets.push_back(new bullet());
	enemyBullets.back()->setPos_x(enemies[i]->getPosX());
	enemyBullets.back()->setPos_y(enemies[i]->getPosY());
	enemyBullets.back()->set_Ang(enemies[i]->getRotation());
	enemyBullets.back()->set_mode(false);
}

void Game::enemy2Fire(int i) {
	//std::cout << i << std::endl;
	enemyBullets.push_back(new bullet());
	int tempX = enemies[i]->getPosX();
	int tempY = enemies[i]->getPosY();
	enemyBullets.back()->setPos_x(tempX);
	enemyBullets.back()->setPos_y(tempY);
	int tempRotation = enemies[i]->getRotation();
	enemyBullets.back()->set_Ang(tempRotation);
	enemyBullets.back()->set_mode(false);
	enemyBullets.push_back(new bullet());
	enemyBullets.back()->setPos_x(tempX);
	enemyBullets.back()->setPos_y(tempY);
	enemyBullets.back()->set_Ang(tempRotation - 20);
	enemyBullets.back()->set_mode(false);
	enemyBullets.push_back(new bullet());
	enemyBullets.back()->setPos_x(tempX);
	enemyBullets.back()->setPos_y(tempY);
	enemyBullets.back()->set_Ang(tempRotation + 20);
	enemyBullets.back()->set_mode(false);
}

void Game::kill()
{
	aliveState = false;
	deathX = player->getPosX();
	deathY = player->getPosY();
}

void Game::init() 
{ 
	graphics::setFont(std::string(ASSET_PATH) + "Font.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "soundtrack.mp3", 0.11f, true);
	starttimer = graphics::getGlobalTime();
}

Game::Game()
{

}

Game::~Game()
{
	if (player && getAliveState())
	{
		delete player;
	}
}
