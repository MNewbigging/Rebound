#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Player.h"



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
    std::vector<Entity*> mBullets;

	// General game setup - called once before main loop
	void SetupGame(vec2 windowSize)
	{
		SetupPlayer();
		mPlayer.SetupBullets(windowSize, mMaxBulletCount, mBulletSize, mBulletSpeed);
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


	
};