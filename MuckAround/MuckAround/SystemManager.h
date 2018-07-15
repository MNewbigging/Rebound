#pragma once

#include "EnemyWaveSystem.h"

class SystemManager
{
public:
	EnemyWaveSystem enemyWave;

	//////////////////////////////////////////////////////////////////////////////

	void Update(std::vector<Enemy> &enemies, float dt)
	{
		enemyWave.Update(enemies, dt);
	}
};