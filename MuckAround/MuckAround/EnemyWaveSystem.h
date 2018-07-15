#pragma once

#include <vector>
#include <random>
#include "Enemies.h"


typedef sf::Vector2f vec2;

class EnemyWaveSystem 
{
public:
	
	int mTotalEnemiesInWave;
	int mEnemiesLeftInWave;
	float mWaveDelayTimer;
	const float mMaxWaveDelayTimer = 10.0f;
	vec2 windowSize;

	/////////////////////////////////////////////////////////////////////////////////
	EnemyWaveSystem();
	~EnemyWaveSystem() {}


	void Update(std::vector<Enemy> &enemies, float dt);

	void BeginNextWave(std::vector<Enemy> &enemies);
};