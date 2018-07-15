#pragma once

#include <vector>
#include <random>
#include "Enemies.h"


typedef sf::Vector2f vec2;

class EnemyWaveSystem 
{
public:
	
	int mTotalEnemiesInWave = 3;
	int mEnemiesLeftInWave = 0;
	float mWaveDelayTimer = 0.0f;
	const float mMaxWaveDelayTimer = 10.0f;
	vec2 windowSize = vec2(0.0f, 0.0f);

	/////////////////////////////////////////////////////////////////////////////////

	void Update(std::vector<Enemy> &enemies, float dt);

	void BeginNextWave(std::vector<Enemy> &enemies);
};