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
	//// Circle 
	//CircleObstacle* obs = new CircleObstacle();
	//// Assign properties
	//obs->mPos = vec2(100.0f, 100.0f);
	//obs->mType = cCircleObsType;
	//obs->mRadius = cCircleObsSize;
	//obs->mColour = cCircleObsColour;
	//// Add it to list
	//mObstacles.push_back(obs);

	LoadLevel();

	// Rectangle
	RectangleObstacle* rec = new RectangleObstacle();
	rec->mPos = vec2(-100.0f, -100.0f);
	rec->mSpeed = 15.0f;
	rec->mType = cRectObsType;
	rec->mSize = cRectObsSize;
	rec->mColour = cRectObsColour;
	rec->mRot = 45;
	rec->FindVertices();
	mObstacles.push_back(rec);
}

void Gamestate::LoadLevel()
{
	// Declare input file stream obj
	std::ifstream levelFile;
	// Open it
	levelFile.open("./Levels/LevelOne.lvl");
	// Read in all lines to container
	std::vector<std::string> lines;
	if (levelFile.is_open())
	{
		std::string line;
		while (std::getline(levelFile, line))
		{
			lines.push_back(line);
		}
	}
	// Parse the level file lines; create obstacles
	for (auto line : lines)
	{
		// Split each line on delimiters, store in another container
		std::stringstream ss(line);
		std::vector<std::string> lineData;
		while (ss.good())
		{
			std::string substr; 
			std::getline(ss, substr, '/');
			lineData.push_back(substr);
		}

		// First substring is the type of obstacle
		int type = std::stoi(lineData[0]);
		switch (type)
		{
		// Circle obstacle
		case 1:
		{
			CreateCircleObstacle(lineData);
			break;
		}

		default:
			break;
		}
	}
}

void Gamestate::CreateCircleObstacle(std::vector<std::string> lineData)
{
	// Second substr is position - split on comma for x and y
	std::stringstream ssPos(lineData[1]);
	std::vector<std::string> posStr;
	while (ssPos.good())
	{
		std::string substr;
		std::getline(ssPos, substr, ',');
		posStr.push_back(substr);
	}
	// Cast the split position string values to floats in pos vec
	vec2 position = vec2(std::stof(posStr[0]), std::stof(posStr[1]));

	// Cast third substr to float to get radius value
	float radius = std::stof(lineData[2]);

	// Cast the final substr to int to get color value
	int colour = std::stoi(lineData[3]);

	// Now create the parsed object & set properties
	CircleObstacle* circleObs = new CircleObstacle();
	circleObs->mType = 1; 
	circleObs->mPos = position;
	circleObs->mRadius = radius;
	circleObs->mColour = sf::Color(colour);
	// Add to list
	mObstacles.push_back(circleObs);

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
