#include "Gamestate.h"

// Deconstructor - delete objects declared new
Gamestate::~Gamestate()
{
	for (auto &o : mObstacles)
	{
		delete(o);
	}
	mObstacles.clear();
}

// General game setup - called once before main loop
void Gamestate::SetupGame(vec2 windowSize)
{
	SetupPlayer();
	SetupBullets(windowSize);
	SetupObstacles();
	SetupEnemies(windowSize);
	SetupSystems(windowSize);
}

void Gamestate::SetupPlayer()
{
	// Set player vars
	mPlayer.mHealth = cPlayerHealth;
	mPlayer.mSpeed = cPlayerSpeed;
	mPlayer.mRadius = cPlayerSize;
	mPlayer.mBulletsFiredLimit = cMaxBulletCount;

	// Spawn in center for now
	mPlayer.mPos = vec2(0.0f, 0.0f);
}

void Gamestate::SetupBullets(vec2 windowSize)
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

void Gamestate::SetupObstacles()
{
	// Circle 
	CircleObstacle* obs = new CircleObstacle();
	// Assign properties
	obs->mPos = vec2(100.0f, 100.0f);
	obs->mType = cCircleObsType;
	obs->mRadius = cCircleObsSize;
	obs->mColour = cCircleObsColour;
	// Add it to list
	mObstacles.push_back(obs);

	// Rectangle
	RectangleObstacle* rec = new RectangleObstacle();
	rec->mPos = vec2(-100.0f, -100.0f);
	rec->mType = cRectObsType;
	rec->mSize = cRectObsSize;
	rec->mColour = cRectObsColour;
	rec->mRot = 45;
	rec->FindVertices();
	mObstacles.push_back(rec);
}

void Gamestate::SetupEnemies(vec2 windowSize)
{
	for (int i = 0; i < cMaxBasicEnemyCount; i++)
	{
		Enemy enemy;
		enemy.mEnemyPoolPos = vec2(windowSize.x + (i * cBasicEnemySize * 2), -windowSize.y - 100);
		enemy.mPos = enemy.mEnemyPoolPos;
		enemy.mRadius = cBasicEnemySize;
		enemy.mSpeed = cBasicEnemySpeed;
		enemy.mHealth = enemy.mMaxHealth = cBasicEnemyMaxHealth;
		enemy.mNormalColor = sf::Color::Magenta;
		enemy.mHitColor = sf::Color::Red;

		mEnemies.push_back(enemy);
	}

}

void Gamestate::SetupSystems(vec2 windowSize)
{
	systemManager.enemyWave.windowSize = windowSize;
}
