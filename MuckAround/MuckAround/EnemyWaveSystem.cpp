#include "EnemyWaveSystem.h"

void EnemyWaveSystem::Update(std::vector<Enemy> &enemies, float dt)
{
	// Check if this wave has finished
	// TODO - find a way to do this without calling every frame
	mEnemiesLeftInWave = mTotalEnemiesInWave;
	for (int i = 0; i < mTotalEnemiesInWave; i++)
	{
		if (!enemies[i].mActive)
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
			BeginNextWave(enemies);
		}
	}
}

void EnemyWaveSystem::BeginNextWave(std::vector<Enemy> &enemies)
{
	// Setup random generators
	std::uniform_real_distribution<float> distroX(0, windowSize.x);
	std::uniform_real_distribution<float> distroY(0, windowSize.y);

	// Reset wave vars
	mEnemiesLeftInWave = mTotalEnemiesInWave;
	mWaveDelayTimer = 10.0f;

	// Iterate through list of enemies in pool, up to wave total
	for (int i = 0; i < mTotalEnemiesInWave; i++)
	{
		std::random_device rd;
		std::default_random_engine rng(rd());

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
		enemies[i].mPos = rnd;
		// Activate this enemy
		enemies[i].mActive = true;
	}
}
