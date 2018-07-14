#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Player.h"
#include "Obstacles.h"
#include "Enemies.h"


typedef sf::Vector2f vec2;

struct Gamestate
{
	// Gameplay variables - only edited here
	const float cPlayerSize       = 25.0f;
	const float cPlayerSpeed	  = 180.0f;
	const float cPlayerHealth	  = 100.0f;

	const float cBulletSize		  = 8.0f;
	const float cBulletSpeed	  = 200.0f;
	const int cMaxBulletCount     = 5;

	const int cCircleObsType   = 1;
	
	const float cBasicEnemySize      = 15.0f;
	const float cBasicEnemySpeed     = 125.0f;
	const float cBasicEnemyMaxHealth = 100.0f;
	const int cMaxBasicEnemyCount    = 1;

	const sf::Color cBasicEnemyNormalColor = sf::Color::Magenta;
	const sf::Color cBasicEnemyHitColor = sf::Color::Red;

	Player mPlayer;

	std::vector<BasicEnemy> mBasicEnemies;
    std::vector<Bullet> mBullets;
	std::vector<Obstacle*> mObstacles;

	// General game setup - called once before main loop
	void SetupGame(vec2 windowSize)
	{
		SetupPlayer();
		SetupBullets(windowSize);
		SetupObstacles();
		SetupEnemies(windowSize);
	}

	Gamestate() {}
	// Deconstructor - delete objects declared new
	~Gamestate() 
	{
		for (auto &o : mObstacles)
		{
			delete(o);
		}
		mObstacles.clear();
	}
private:

	void SetupPlayer()
	{
		// Set player vars
		mPlayer.mHealth = cPlayerHealth;
		mPlayer.mSpeed = cPlayerSpeed;
		mPlayer.mRadius = cPlayerSize;
		mPlayer.mBulletsFiredLimit = cMaxBulletCount;

		// Spawn in center for now
		mPlayer.mPos = vec2(0.0f, 0.0f);
	}

	void SetupBullets(vec2 windowSize)
	{
		for (int i = 0; i < cMaxBulletCount; i++)
		{
			Bullet bullet;

			// Make sure to spread out each bullet - each has unqiue place to reset to
			bullet.mBulletPoolPos = vec2(windowSize.x + (i * cBulletSize * 2), windowSize.y + 100);
			bullet.mPos = bullet.mBulletPoolPos;
			// Set default bullet speed
			bullet.mSpeed = cBulletSpeed;
			// Set radius
			bullet.mRadius = cBulletSize;
			// Add to pool
			mBullets.push_back(bullet);
		}
	}
	
	// Starting obstacles
	void SetupObstacles()
	{
		CircleObstacle* obs = new CircleObstacle();

		obs->mType = cCircleObsType;
		obs->mPos = vec2(100.0f, 100.0f);
		obs->mRadius = 40.0f;
		obs->mColour = sf::Color::Green;

		mObstacles.push_back(obs);
	}

	void SetupEnemies(vec2 windowSize)
	{
		for (int i = 0; i < cMaxBasicEnemyCount; i++)
		{
			BasicEnemy enemy;
			enemy.mEnemyPoolPos = vec2(windowSize.x + (i * cBasicEnemySize * 2), -windowSize.y - 100);
			enemy.mPos = enemy.mEnemyPoolPos;
			enemy.mRadius = cBasicEnemySize;
			enemy.mSpeed = cBasicEnemySpeed;
			enemy.mHealth = enemy.mMaxHealth = cBasicEnemyMaxHealth;
			enemy.mNormalColor = sf::Color::Magenta;
			enemy.mHitColor = sf::Color::Red;

			mBasicEnemies.push_back(enemy);
		}
	
	}
};