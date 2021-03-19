#include "Game.h"
#include "graphics.h"
#include "config.h"

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "Font.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "soundtrack.mp3", 0.11f, true);
	br.texture = std::string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;
} 

void Game::update()
{
	if (gameState == startMenu)
	{
		StartMenu();
	}
	else if (gameState == gamePlay)
	{
		GameUpdate();
	}
}

void Game::StartMenu()
{
	if (!startMenuInitialized) startMenuInit();

	if (graphics::getKeyState(graphics::SCANCODE_1)) spaceshipPos = 1;
	if (graphics::getKeyState(graphics::SCANCODE_2)) spaceshipPos = 2;
	if (graphics::getKeyState(graphics::SCANCODE_3)) spaceshipPos = 3;

	for (int i = 0; i < tempPlayers.size(); i++) {
		tempPlayers[i]->update();
		if (i+1==spaceshipPos)tempPlayers[i]->setSelected(true);
		else tempPlayers[i]->setSelected(false);
	}

	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		gameState = gamePlay;
		for (int i = 0; i < tempPlayers.size(); i++) { 
			delete tempPlayers[i];
		}
		tempPlayers.clear();
			
	}

}

void Game::startMenuInit() {

	for (int i = 0; i < 3; i++) {
		tempPlayers.push_back(new Player(CANVAS_WIDTH / 2 + (i - 1) * 150, CANVAS_HEIGHT / 2 + 200, true));
		tempPlayers.back()->setSpaceshipType(i + 1);
	}
	startMenuInitialized = true;
	starttimer = graphics::getGlobalTime();

}

void Game::GameUpdate()
{

	if (!player_initialized)spawnPlayer();

	updateGameObjects();

	if (player)checkPlayerFire();

	if (!finalBoss)spawnEnemies();

	if (enemiesKilled >= enemiesTilBoss && enemiesSpawned >= enemiesTilBoss && !finalBoss) spawnFinalBoss();

	if (finalBoss)checkFinalBossFire();

	CheckCollision();

	if (player && player->getLives() <= 0)killPlayer();

	if (!player && graphics::getKeyState(graphics::SCANCODE_R))restart();

}

void Game::spawnPlayer() {
	player = new Player();
	player->setSpaceshipType(spaceshipPos);
	player_initialized = true;
	player->setPowerupType(-1);
	lastTime = -3500;
	lastTimeEnemy = graphics::getGlobalTime();
	lastTimeEnemy2 = graphics::getGlobalTime();
	lastTimeEnemy3 = graphics::getGlobalTime();
	lastTimeEnemy4 = graphics::getGlobalTime();
	lastTimeSpawnedPowerup = 0;
	lastTimeActivatedPowerup = 0;
	cooldown = 2000;
	cooldown2 = 3000;
	cooldown3 = 7000;
	cooldown4 = 8000;
	enemyCounter = 0;
	enemyCounter2 = 0;
	enemyCounter3 = 0;
	enemyCounter4 = 0;
	enemiesKilled = 0;
	enemiesSpawned = 0;
	powerupCounter = 0;
	score = 0;
	i = 0;
	j = 0;
	CountBullets = 0;
}

void Game::updateGameObjects() {

	if (player) {
		player->update();
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

	enemies::setPlayerX(player ? player->getPosX() : deathX);
	enemies::setPlayerY(player ? player->getPosY() : deathY);

	while (i < enemies.size()) {
		enemies[i]->update();
		srand(graphics::getGlobalTime() + rand());
		if (player && graphics::getGlobalTime() - enemies[i]->getLastTimeFired() > 2000 + rand() % 100000 && graphics::getGlobalTime() > 3000 && enemies[i]->getTransformState()) {
			enemyFireTriple(i);
			enemies[i]->setLastTimeFired(graphics::getGlobalTime());
		}
		else if (player && graphics::getGlobalTime() - enemies[i]->getLastTimeFired() > 2000 + rand() % 100000 && graphics::getGlobalTime() > 3000 && !enemies[i]->getTransformState()) {
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
			continue;
		}
		i++;
	}

	i = 0;

	if (finalBoss) {
		if (finalBoss->isAlive())finalBoss->update();
		else {
			delete finalBoss;
			finalBoss = nullptr;
		}
	}
}

void Game::checkPlayerFire() {

	graphics::getMouseState(mouse);

	if (player && mouse.button_left_pressed && shouldFire)
	{
		if (player->getPowerupType() != 1)playerFire();
		else playerFireTriple();

		if (CountBullets >= 8)
		{
			graphics::playSound(std::string(ASSET_PATH) + "lastfire.ogg", 0.5f);
		}
		else
		{
			graphics::playSound(std::string(ASSET_PATH) + "primaryfire.ogg", 0.5f);
		}
	}

	if (player && CountBullets == 0)reloadTimer = graphics::getGlobalTime();

	if (player && graphics::getGlobalTime() - reloadTimer > 2500)
	{
		if (CountBullets > 0)CountBullets--;
		reloadTimer = graphics::getGlobalTime();
	}

	if (CountBullets >= 8) {
		shouldFire = false;
		lastTime = graphics::getGlobalTime();
		CountBullets = 0;
	}

	if (graphics::getGlobalTime() - lastTime > 3500) {
		shouldFire = true;
	}

}

void Game::spawnEnemies() {

	if (graphics::getGlobalTime() - lastTimeEnemy > cooldown && enemiesSpawned <= enemiesTilBoss) {
		enemies.push_back(new enemy());
		enemies.back()->setXY();
		lastTimeEnemy = graphics::getGlobalTime();
		enemies.back()->setLastTimeFired(graphics::getGlobalTime() - 1000);
		enemyCounter++;
		if (enemyCounter / 10 != 0 && cooldown > 500) {
			enemyCounter = 0;
			cooldown -= 100;
		}
		enemiesSpawned++;
	}

	if (graphics::getGlobalTime() - lastTimeEnemy2 > cooldown2 && enemiesSpawned <= enemiesTilBoss) {
		enemies2.push_back(new enemy2());
		enemies2.back()->setXY();
		lastTimeEnemy2 = graphics::getGlobalTime();
		enemyCounter2++;
		if (enemyCounter2 / 10 != 0 && cooldown2 > 500) {
			enemyCounter2 = 0;
			cooldown2 -= 100;
		}
		enemiesSpawned++;
	}

	if (graphics::getGlobalTime() - lastTimeEnemy3 > cooldown3 && score > 1200 && enemiesSpawned <= enemiesTilBoss) {
		enemies.push_back(new enemy3());
		enemies.back()->setXY();
		lastTimeEnemy3 = graphics::getGlobalTime();
		enemies.back()->setLastTimeFired(graphics::getGlobalTime() - 1000);
		enemyCounter++;
		if (enemyCounter3 / 10 != 0 && cooldown3 > 2000) {
			enemyCounter3 = 0;
			cooldown3 -= 100;
		}
		enemiesSpawned++;
	}

	if (graphics::getGlobalTime() - lastTimeEnemy4 > cooldown4 && score > 1400 && enemiesSpawned <= enemiesTilBoss) {
		enemies2.push_back(new enemy4(false));
		enemies2.back()->setXY();
		lastTimeEnemy4 = graphics::getGlobalTime();
		enemyCounter4++;
		if (enemyCounter4 / 10 != 0 && cooldown4 > 2000) {
			enemyCounter4 = 0;
			cooldown4 -= 100;
		}
		enemiesSpawned++;
	}

}

void Game::spawnFinalBoss() {
	finalBoss = new boss();
	phaseTwoShots = 0;
	enemiesKilled = 0;
	enemiesSpawned = 0;
	lastTimeShotPhaseOne = graphics::getGlobalTime();
	lastTimeShotPhaseTwo = graphics::getGlobalTime();
}

void Game::checkFinalBossFire() {
	if (finalBoss->isAtPlace()) {
		if (finalBoss->getChangedLocation() % 5 == 0 && graphics::getGlobalTime() - lastTimeShotPhaseTwo > phaseTwoCooldown && phaseTwoShots < 5 && !spawnedBossMinions) bossFireUlti();
		else if (phaseTwoShots > 4)spawnBossMinions();
		else if (finalBoss->getChangedLocation() % 5 != 0 && graphics::getGlobalTime() - lastTimeShotPhaseOne > phaseOneCooldown)bossFireTriple();
	}
}

void Game::CheckCollision() {

	float radius;
	if (player) {
		radius = (player->getPowerupType() == 0) ? player->getRadius() + 25 : player->getRadius();
	}

	if (player) {
		while (i < enemies.size()) {
			if (sqrt(pow(player->getPosX() - enemies[i]->getPosX(), 2) + pow(player->getPosY() - enemies[i]->getPosY(), 2)) - radius - enemies[i]->getRadius() < 0) {
				if (player->getPowerupType() != 0)player->hit();
				else lastTimeActivatedPowerup = lastTimeActivatedPowerup - 2500;
				if (enemies[i]->isActive()) {
					enemies[i]->setInactive();
					delete enemies[i];
					enemies.erase(enemies.begin() + i);
				}
				if (!finalBoss)enemiesKilled++;
				continue;
			}
			i++;
		}
		i = 0;
	}

	if (player) {
		while (i < enemies2.size()) {
			if (sqrt(pow(player->getPosX() - enemies2[i]->getPosX(), 2) + pow(player->getPosY() - enemies2[i]->getPosY(), 2)) - radius - enemies2[i]->getRadius() < 0) {
				if (player->getPowerupType() != 0)player->hit();
				else lastTimeActivatedPowerup = lastTimeActivatedPowerup - 2500;
				if (!finalBoss && !enemies2[i]->getMultiplied())enemiesKilled++;
				if (enemies2[i]->isActive()) {
					enemies2[i]->setInactive();
					delete enemies2[i];
					enemies2.erase(enemies2.begin() + i);
				}
				continue;
			}
			i++;
		}
		i = 0;
	}

	if (player) {
		while (i < enemyBullets.size()) {
			if (sqrt(pow(player->getPosX() - enemyBullets[i]->getPosX(), 2) + pow(player->getPosY() - enemyBullets[i]->getPosY(), 2)) - radius - enemyBullets[i]->getRadius() < 0) {
				if (player->getPowerupType() != 0)player->hit();
				else lastTimeActivatedPowerup = lastTimeActivatedPowerup - 2500;
				if (enemyBullets[i]->isActive()) {
					delete enemyBullets[i];
					enemyBullets.erase(enemyBullets.begin() + i);
				}
				break;
			}
			i++;
		}
		i = 0;
	}

	while (i < bullets.size()) {
		while (j < enemies.size()) {
			if (sqrt(pow(bullets[i]->getPosX() - enemies[j]->getPosX(), 2) + pow(bullets[i]->getPosY() - enemies[j]->getPosY(), 2)) - bullets[i]->getRadius() - enemies[j]->getRadius() < 0) {
				if (!enemies[j]->getTransformState())score += 50;
				else score += 150;
				lastTime = -3500;
				shouldFire = true;
				CountBullets = 0;
				if (bullets[i]->isActive() && enemies[j]->isActive()) {
					if (bullets[i]->get_mode() != 2) {
						delete bullets[i];
						bullets.erase(bullets.begin() + i);
					}
					if (player && player->getPowerupType() < 0 && !power && powerupCounter < 9)powerupCounter++;
					else if (player && player->getPowerupType() < 0 && powerupCounter >= 9 && !power) {
						srand(graphics::getGlobalTime());
						power = new powerup();
						lastTimeSpawnedPowerup = graphics::getGlobalTime();
						power->setType(rand() % 4);
						power->setPosX(enemies[j]->getPosX());
						power->setPosY(enemies[j]->getPosY());
					}
					if (!finalBoss)enemiesKilled++;
					delete enemies[j];
					enemies.erase(enemies.begin() + j);
					i--;
					break;
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
				if (!enemies2[j]->getTransformState())score += 100;
				else score += 200;
				lastTime = -3500;
				shouldFire = true;
				CountBullets = 0;
				if (bullets[i]->isActive() && enemies2[j]->isActive()) {
					if (player && player->getPowerupType() != 2) {
						delete bullets[i];
						bullets.erase(bullets.begin() + i);
					}
					if (enemies2[j]->getTransformState() && !enemies2[j]->getMultiplied()) {
						enemies2.push_back(new enemy4(true, enemies2[j]->getPosX(), enemies2[j]->getPosY()));
						enemies2.push_back(new enemy4(true, enemies2[j]->getPosX(), enemies2[j]->getPosY(), 120));
						enemies2.push_back(new enemy4(true, enemies2[j]->getPosX(), enemies2[j]->getPosY(), -120));
					}
					if (player && player->getPowerupType() < 0 && !power && powerupCounter < 9)powerupCounter++;
					else if (player && player->getPowerupType() < 0 && powerupCounter >= 9 && !power) {
						srand(graphics::getGlobalTime());
						power = new powerup();
						lastTimeSpawnedPowerup = graphics::getGlobalTime();
						power->setType(rand() % 4);
						power->setPosX(enemies2[j]->getPosX());
						power->setPosY(enemies2[j]->getPosY());
					}
					if (!finalBoss && !enemies2[j]->getMultiplied())enemiesKilled++;
					delete enemies2[j];
					enemies2.erase(enemies2.begin() + j); 
					i--;
					break;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}

	i = 0;

	if (player && finalBoss) {

		if (sqrt(pow(player->getPosX() - finalBoss->getPosX(), 2) + pow(player->getPosY() - finalBoss->getPosY(), 2)) - radius - finalBoss->getRadius() < 0) {
			if (player->getPowerupType() != 0)player->hit();
			else lastTimeActivatedPowerup = lastTimeActivatedPowerup - 2500;
			finalBoss->hit();
		}
	}

	if (player && finalBoss) {
		while (i < bullets.size()) {
			if (sqrt(pow(finalBoss->getPosX() - bullets[i]->getPosX(), 2) + pow(finalBoss->getPosY() - bullets[i]->getPosY(), 2)) - finalBoss->getRadius() - bullets[i]->getRadius() < 0) {
				lastTime = -3500;
				shouldFire = true;
				CountBullets = 0;
				finalBoss->hit();
				if (bullets[i]->isActive()) {
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
				}
				break;
			}
			i++;
		}
		i = 0;
	}

	if ((player && power && player->getPowerupType() < 0 && sqrt(pow(player->getPosX() - power->getPosX(), 2) + pow(player->getPosY() - power->getPosY(), 2)) - player->getRadius() - power->getRadius() < 0)) {
		player->setPowerupType(power->getType());
		lastTimeActivatedPowerup = graphics::getGlobalTime();
		powerupCounter = 0;
		delete power;
		power = nullptr;
	}

	if (power && graphics::getGlobalTime() - lastTimeSpawnedPowerup > spawnedPowerupCooldown) {
		powerupCounter = 0;
		delete power;
		power = nullptr;
	}

	if (player && graphics::getGlobalTime() - lastTimeActivatedPowerup > activatedPowerupCooldown) {
		player->setPowerupType(-1);
	}
}

void Game::killPlayer()
{
	deathX = player->getPosX();
	deathY = player->getPosY();
	delete player;
	player = nullptr;
}

void Game::restart() {

	player_initialized = false;
	for (int i = 0; i < enemies.size(); i++)delete enemies[i];
	enemies.clear();
	for (int i = 0; i < enemies2.size(); i++)delete enemies2[i];
	enemies2.clear();
	for (int i = 0; i < bullets.size(); i++)delete bullets[i];
	bullets.clear();
	for (int i = 0; i < enemyBullets.size(); i++)delete enemyBullets[i];
	enemyBullets.clear();
	if (finalBoss) {
		delete finalBoss;
		finalBoss = nullptr;
	}
	if (power) {
		delete power;
		power = nullptr;
	}
	replayTime = graphics::getGlobalTime();

}

void Game::draw()
{
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	if (gameState == startMenu)
	{
		StartMenuDraw();
	}
	else if (gameState == gamePlay)
	{
		GameUpdateDraw();
	}
}

void Game::StartMenuDraw()
{

	if (graphics::getGlobalTime() - starttimer > 800 ) {
		MenuFlash = !MenuFlash;
		starttimer = graphics::getGlobalTime();
	}

	if (MenuFlash) graphics::drawText(CANVAS_WIDTH / 5.5, CANVAS_HEIGHT / 2, CANVAS_WIDTH/16, "Press ENTER to Start", br);

	graphics::drawText(CANVAS_WIDTH / 2 - 75, CANVAS_HEIGHT - 50, CANVAS_WIDTH / 64, "Shoot -> click", br);
	graphics::drawText(CANVAS_WIDTH / 2-150, CANVAS_HEIGHT-25, CANVAS_WIDTH / 64, "Move -> WASD or arrows", br);
	
	for (int i = 0; i < tempPlayers.size(); i++)tempPlayers[i]->draw();

	graphics::drawText(CANVAS_WIDTH / 2 - 110, CANVAS_HEIGHT / 2 + 250, 30, "1", br);
	graphics::drawText(CANVAS_WIDTH / 2 +40, CANVAS_HEIGHT / 2 + 250, 30, "2", br);
	graphics::drawText(CANVAS_WIDTH / 2 + 190, CANVAS_HEIGHT / 2 + 250, 30,"3", br);
	
}

void Game::GameUpdateDraw()
{
	
	drawGameObjects();

	sprintf_s(playerScore, "Score:%d", score);
	graphics::drawText(20, 50, CANVAS_WIDTH/32, playerScore, br);
	
	if (!player & player_initialized)graphics::drawText(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 2, CANVAS_WIDTH/22.85, "Press R to Restart", br);

	if (graphics::getGlobalTime() > 250 && graphics::getGlobalTime() - replayTime <= 250) { graphics::drawText(CANVAS_WIDTH / 3- 16*(graphics::getGlobalTime() - replayTime), CANVAS_HEIGHT / 2+ (graphics::getGlobalTime() - replayTime)*1.25, CANVAS_WIDTH/22.8+4*(graphics::getGlobalTime()-replayTime), "Press R to Restart", br); }

}

void Game::drawGameObjects() { 

	if (player)player->draw();

	if (player && player->getPowerupType() == 0) {
		shieldBr.outline_opacity = 0.0f;
		shieldBr.fill_secondary_color[0] = 0.79f;
		shieldBr.fill_secondary_color[1] = 0.17f;
		shieldBr.fill_secondary_color[2] = 0.57f;
		shieldBr.fill_color[0] = 0.0f;
		shieldBr.fill_color[1] = 0.6f;
		shieldBr.fill_color[2] = 0.0f;
		shieldBr.fill_opacity = 0.75f;
		shieldBr.fill_secondary_opacity = 0.3f;
		shieldBr.gradient = true;
		graphics::drawDisk(player->getPosX(), player->getPosY(), player->getRadius() + 25, shieldBr);
	}

	if (power)power->draw();

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

	if (finalBoss)finalBoss->draw();

}

void Game::playerFire() {
	bullets.push_back(new bullet());
	bullets.back()->setPos_x(player->getPosX());
	bullets.back()->setPos_y(player->getPosY());
	bullets.back()->set_Ang(player->getAng());
	if (player->getPowerupType() == 2)bullets.back()->set_mode(2);
	else bullets.back()->set_mode(0);
	CountBullets++;
}

void Game::playerFireTriple() {
	bullets.push_back(new bullet());
	int tempX = player->getPosX();
	int tempY = player->getPosY();
	bullets.back()->setPos_x(tempX);
	bullets.back()->setPos_y(tempY);
	int tempRotation = player->getAng();
	bullets.back()->set_Ang(tempRotation);
	bullets.back()->set_mode(3);
	bullets.push_back(new bullet());
	bullets.back()->setPos_x(tempX);
	bullets.back()->setPos_y(tempY);
	bullets.back()->set_Ang(tempRotation - 20);
	bullets.back()->set_mode(3);
	bullets.push_back(new bullet());
	bullets.back()->setPos_x(tempX);
	bullets.back()->setPos_y(tempY);
	bullets.back()->set_Ang(tempRotation + 20);
	bullets.back()->set_mode(3);
	CountBullets++;
}

void Game::enemyFire(int i) {
	enemyBullets.push_back(new bullet());
	enemyBullets.back()->setPos_x(enemies[i]->getPosX());
	enemyBullets.back()->setPos_y(enemies[i]->getPosY());
	enemyBullets.back()->set_Ang(enemies[i]->getRotation());
	enemyBullets.back()->set_mode(1);
}

void Game::enemyFireTriple(int i) {
	enemyBullets.push_back(new bullet());
	int tempX = enemies[i]->getPosX();
	int tempY = enemies[i]->getPosY();
	int tempRotation = enemies[i]->getRotation();
	enemyBullets.back()->setPos_x(tempX);
	enemyBullets.back()->setPos_y(tempY);
	enemyBullets.back()->set_Ang(tempRotation);
	enemyBullets.back()->set_mode(1);
	enemyBullets.push_back(new bullet());
	enemyBullets.back()->setPos_x(tempX);
	enemyBullets.back()->setPos_y(tempY);
	enemyBullets.back()->set_Ang(tempRotation - 20);
	enemyBullets.back()->set_mode(1);
	enemyBullets.push_back(new bullet());
	enemyBullets.back()->setPos_x(tempX);
	enemyBullets.back()->setPos_y(tempY);
	enemyBullets.back()->set_Ang(tempRotation + 20);
	enemyBullets.back()->set_mode(1);
}

void Game::bossFireTriple() {
	spawnedBossMinions = false;
	enemyBullets.push_back(new bullet());
	int tempX = finalBoss->getPosX();
	int tempY = finalBoss->getPosY();
	enemyBullets.back()->setPos_x(tempX);
	enemyBullets.back()->setPos_y(tempY);
	int tempRotation = finalBoss->getRotation();
	enemyBullets.back()->set_Ang(tempRotation);
	enemyBullets.back()->set_mode(1);
	enemyBullets.push_back(new bullet());
	enemyBullets.back()->setPos_x(tempX);
	enemyBullets.back()->setPos_y(tempY);
	enemyBullets.back()->set_Ang(tempRotation - 20);
	enemyBullets.back()->set_mode(1);
	enemyBullets.push_back(new bullet());
	enemyBullets.back()->setPos_x(tempX);
	enemyBullets.back()->setPos_y(tempY);
	enemyBullets.back()->set_Ang(tempRotation + 20);
	enemyBullets.back()->set_mode(1);
	lastTimeShotPhaseOne = graphics::getGlobalTime();
}

void Game::bossFireUlti() {
	for (int i = 0; i < 36; i++) {
		enemyBullets.push_back(new bullet());
		enemyBullets.back()->setPos_x(finalBoss->getPosX());
		enemyBullets.back()->setPos_y(finalBoss->getPosY());
		enemyBullets.back()->set_Ang(finalBoss->getRotation() + i * 10);
		enemyBullets.back()->set_mode(1);
	}
	lastTimeShotPhaseTwo = graphics::getGlobalTime();
	phaseTwoShots++;
}

void Game::spawnBossMinions() {
	phaseTwoShots = 0;
	if (finalBoss->getLives() > finalBoss->getMaxHP() / 4) {
		for (int i = 0; i < 5; i++) {
			enemies.push_back(new enemy());
			enemies.back()->setXY(finalBoss->getPosX(), finalBoss->getPosY());
			enemies.back()->setLastTimeFired(graphics::getGlobalTime() - 1000);
		}
		enemies2.push_back(new enemy2());
		enemies2.back()->setXY(finalBoss->getPosX(), finalBoss->getPosY() + 100);
		enemies2.push_back(new enemy2());
		enemies2.back()->setXY(finalBoss->getPosX(), finalBoss->getPosY() - 100);
		enemies2.push_back(new enemy2());
		enemies2.back()->setXY(finalBoss->getPosX() - 100, finalBoss->getPosY());
		enemies2.push_back(new enemy2());
		enemies2.back()->setXY(finalBoss->getPosX() + 100, finalBoss->getPosY());
	}
	else {
		for (int i = 0; i < 5; i++) {
			enemies.push_back(new enemy3());
			enemies.back()->setXY(finalBoss->getPosX(), finalBoss->getPosY());
			enemies.back()->setLastTimeFired(graphics::getGlobalTime() - 1000);
		}
		enemies2.push_back(new enemy4(false));
		enemies2.back()->setXY(finalBoss->getPosX(), finalBoss->getPosY() + 100);
		enemies2.push_back(new enemy4(false));
		enemies2.back()->setXY(finalBoss->getPosX(), finalBoss->getPosY() - 100);
		enemies2.push_back(new enemy4(false));
		enemies2.back()->setXY(finalBoss->getPosX() - 100, finalBoss->getPosY());
		enemies2.push_back(new enemy4(false));
		enemies2.back()->setXY(finalBoss->getPosX() + 100, finalBoss->getPosY());
	}
	spawnedBossMinions = true;
}

Game::Game()
{

}

Game::~Game()
{

	for (int i = 0; i < bullets.size(); i++)delete bullets[i];

	for (int i = 0; i < enemyBullets.size(); i++)delete enemyBullets[i];

	for (int i = 0; i < enemies.size(); i++)delete enemies[i];

	for (int i = 0; i < enemies2.size(); i++)delete enemies2[i];

	for (int i = 0; i < tempPlayers.size(); i++)delete tempPlayers[i];

	if (finalBoss)delete finalBoss;

	if (power)delete power;

	if (player)delete player;

}
