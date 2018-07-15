#pragma once

#include <SFML\Graphics.hpp>

#include "HelperFunctions.h"
#include "Entity.h"
#include "Obstacles.h"
#include "Bullets.h"


typedef sf::Vector2f vec2;

class Enemy : public Entity
{
public:
	vec2 mEnemyPoolPos;
	bool mActive;
	sf::Color mColor;
	sf::Color mNormalColor;
	sf::Color mHitColor;

	//////////////////////////////////////////////////////////////////////////////
	Enemy();
	~Enemy() {}

	void Update(vec2 playerPos, float dt);

	void MoveToEnemyPool();

	void DetectCollisions(std::vector<Enemy> enemies, std::vector<Obstacle*> obstacles, std::vector<Bullet> &bullets, float dt);

	void CheckAgainstCircleObstacle(CircleObstacle* circleObs, float dt);
		
	void CheckAgainstRectangleObstacle(RectangleObstacle* rectObs, float dt);

	void CheckAgainstBullets(std::vector<Bullet> &bullets);
	
	void CheckAgainstEnemies(std::vector<Enemy> enemies, float dt);

	void Render(sf::RenderWindow* renderWin);

};