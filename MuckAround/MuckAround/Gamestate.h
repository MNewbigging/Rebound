#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Player.h"
#include "SystemManager.h"


typedef sf::Vector2f vec2;

struct Gamestate
{
	// Player vars
	const float cPlayerSize       = 25.0f;
	const float cPlayerSpeed	  = 180.0f;
	const float cPlayerHealth	  = 100.0f;
	// Bullets
	const float cBulletSize		  = 8.0f;
	const float cBulletSpeed	  = 250.0f;
	const int cMaxBulletCount     = 5;
	// Obstacles
	const int cCircleObsType		 = 1;
	const float cCircleObsSize		 = 40.0f;
	const sf::Color cCircleObsColour  = sf::Color::Green;
	const int cRectObsType			 = 2;
	const vec2 cRectObsSize			 = vec2(20.f, 100.0f);
	const sf::Color cRectObsColour	 = sf::Color::Blue;
	// Enemies
	const float cBasicEnemySize      = 15.0f;
	const float cBasicEnemySpeed     = 125.0f;
	const float cBasicEnemyMaxHealth = 100.0f;
	const int cMaxBasicEnemyCount    = 3;
	int mEnemyWaveSize				 = 3;
	const sf::Color cBasicEnemyNormalColor = sf::Color::Magenta;
	const sf::Color cBasicEnemyHitColor = sf::Color::Red;

	// Game objects
	Player mPlayer;
	std::vector<Enemy> mEnemies;
    std::vector<Bullet> mBullets;
	std::vector<Obstacle*> mObstacles;

	// Systems
	SystemManager systemManager;

	/////////////////////////////////////////////////////////////////////
	Gamestate() {}
	~Gamestate();

	void SetupGame(vec2 windowSize);

private:

	void SetupPlayer();

	void SetupBullets(vec2 windowSize);
	
	void SetupObstacles();

	void SetupEnemies(vec2 windowSize);

	void SetupSystems(vec2 windowSize);

};