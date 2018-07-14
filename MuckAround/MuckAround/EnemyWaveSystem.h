#pragma once

#include "Enemies.h"
#include <vector>
#include <random>

typedef sf::Vector2f vec2;

class EnemyWaveSystem
{
public:
	
	int mTotalEnemiesInWave		   = 1;
	int mEnemiesLeftInWave         = 0;
	float mWaveDelayTimer	       = 0.0f;
	const float mMaxWaveDelayTimer = 10.0f;
	vec2 windowSize			       = vec2(0.0f, 0.0f);


	/////////////////////////////////////////////////////////////////////////////////

	EnemyWaveSystem() {}

	~EnemyWaveSystem() {}


	void Update(float dt) 
	{
		mEnemiesLeftInWave = mTotalEnemiesInWave;
		// Check if this wave has finished
		// TODO - find a way to do this without calling every frame
		// TODO - refactor this horrible code
		for (int i = 0; i < mTotalEnemiesInWave; i++)
		{
			if (!Gamestate::mEnemies[i].mActive)
			{
				mEnemiesLeftInWave--;
			}
		}

		if (mEnemiesLeftInWave == 0)
		{
			mWaveDelayTimer -= dt;
			// Check if next wave should start
			if (mWaveDelayTimer <= 0)
			{
				BeginNextWave();
			}
		}
	}

	void BeginNextWave()
	{
		// Setup random generators
		std::uniform_real_distribution<float> distroX(0, windowSize.x);
		std::uniform_real_distribution<float> distroY(0, windowSize.y);
		std::random_device rd;
		std::default_random_engine rng( rd() );
		// Reset wave vars
		mEnemiesLeftInWave = mTotalEnemiesInWave;
		mWaveDelayTimer = 10.0f;

		// Iterate through list of enemies in pool, up to wave total
		for (int i = 0; i < mTotalEnemiesInWave; i++)
		{
			// 1 - find random point within screen
			vec2 rnd = (windowSize * 0.5f) - vec2(distroX(rng), distroY(rng));
			// 2 - Move it offscreen depending on quadrant
			if (rnd.x > 0)
				rnd.x += (windowSize.x * 0.5f);
			else
				rnd.x -= (windowSize.x * 0.5f);
			if (rnd.y > 0)
				rnd.y += (windowSize.y * 0.5f);
			else
				rnd.y -= (windowSize.y * 0.5f);
			// 3 - assign to this enemy
			Gamestate::mEnemies[i].mPos = rnd;
			// Activate this enemy
			Gamestate::mEnemies[i].mActive = true;
		}
	}
};