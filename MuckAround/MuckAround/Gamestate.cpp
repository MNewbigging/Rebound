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
	SetupEnemies(windowSize);
	LoadLevel();
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

// TODO - remove this after parser can handle rectangles
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


	// Rectangle
	//RectangleObstacle* rec = new RectangleObstacle();
	//rec->mPos = vec2(-100.0f, -100.0f);
	//rec->mSpeed = 15.0f;
	//rec->mType = cRectObsType;
	//rec->mSize = cRectObsSize;
	//rec->mColour = cRectObsColour;
	//rec->mRot = 45;
	//rec->FindVertices();
	//mObstacles.push_back(rec);
}

void Gamestate::LoadLevel()
{
	// Declare input file stream obj
	std::ifstream levelFile;
	// Open it to chosen level 
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
			CircleObstacle* circleObs = new CircleObstacle();
			// Second substring is position data
			circleObs->mPos = ParseVec2(lineData[1]);
			// Third substring is radius value
			circleObs->mRadius = ParseFloat(lineData[2]);
			// Final substring is color value
			circleObs->mColour = sf::Color(ParseColour(lineData[3]));
			// Add to list
			mObstacles.push_back(circleObs);
			break;
		}
		// Rectangle obstacle
		case 2:
		{
			RectangleObstacle* rectObs = new RectangleObstacle();
			// Second substr is position
			rectObs->mPos = ParseVec2(lineData[1]);
			// Third substr is size
			rectObs->mSize = ParseVec2(lineData[2]);
			// Fourth substr is rotation
			rectObs->mRot = ParseFloat(lineData[3]);
			// Final substr is color
			rectObs->mColour = ParseColour(lineData[4]);
			// Init vertices for this rect
			rectObs->FindVertices();
			// Add to list
			mObstacles.push_back(rectObs);
			break;
		}
		default:
			break;
		}
	}
}

vec2 Gamestate::ParseVec2(std::string vecString)
{
	// Split the given string on comma
	std::stringstream ss(vecString);
	std::vector<std::string> substrings;
	while (ss.good())
	{
		std::string temp;
		std::getline(ss, temp, ',');
		substrings.push_back(temp);
	}
	// Cast the split position string values to floats in pos vec
	return vec2(std::stof(substrings[0]), std::stof(substrings[1]));
}

float Gamestate::ParseFloat(std::string floatString)
{
	// Cast given string to float
	return std::stof(floatString);
}

int Gamestate::ParseInt(std::string intString)
{
	// Cast given string to int
	return std::stoi(intString);
}

sf::Color Gamestate::ParseColour(std::string colourString)
{
	// Split given string on commas
	std::stringstream ss(colourString);
	std::vector<std::string> substrings;
	while (ss.good())
	{
		std::string temp;
		std::getline(ss, temp, ',');
		substrings.push_back(temp);
	}
	
	return sf::Color(std::stoi(substrings[0]), std::stoi(substrings[1]),
					 std::stoi(substrings[2]), std::stoi(substrings[3]));
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
