#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Player.h"
#include "Obstacles.h"


typedef sf::Vector2f vec2;

struct Gamestate
{
	// Gameplay variables - only edited here
	const float mPlayerSize     = 15.0f;
	const float mPlayerSpeed	= 180.0f;
	const float mPlayerHealth	= 100.0f;

	const float mBulletSize		= 10.0f;
	const float mBulletSpeed	= 200.0f;
	const int mMaxBulletCount   = 3;


	Player mPlayer;

	//vector<Entity*> mEnemies;
    std::vector<Bullet> mBullets;
	std::vector<Obstacle> mObstacles;

	// General game setup - called once before main loop
	void SetupGame(vec2 windowSize)
	{
		SetupPlayer();
		SetupBullets(windowSize);
		SetupObstacles();
	}

private:

	void SetupPlayer()
	{
		// Set player vars
		mPlayer.mHealth = mPlayerHealth;
		mPlayer.mSpeed = mPlayerSpeed;
		mPlayer.mRadius = mPlayerSize;

		// Spawn in center for now
		mPlayer.mPos = vec2(0.0f, 0.0f);
	}

	// Use bullet pool to avoid new/delete operations at runtime
	void SetupBullets(vec2 offScreenPos)
	{
		for (int i = 0; i < mMaxBulletCount; i++)
		{
			//Entity *bptr;
			Bullet bullet;
			//bptr = &bullet;

			// Make sure to spread out each bullet - each has unqiue place to reset to
			bullet.mBulletPoolPos = vec2(offScreenPos.x + (i * mBulletSize * 2), offScreenPos.y + 100);
			// Set default bullet speed
			bullet.mSpeed = mBulletSpeed;
			// Set radius
			bullet.mRadius = mBulletSize;
			// Add to pool
			mBullets.push_back(bullet);
		}
	}
	
	void SetupObstacles()
	{
		Obstacle obs;

		obs.mPos = vec2(0.0f, 0.0f);
		obs.mRadius = 40.0f;
		obs.mColour = sf::Color::Green;

		mObstacles.push_back(obs);
	}

};