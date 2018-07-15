#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Entity.h"
#include "Bullets.h"
#include "Resources.h"
#include "HelperFunctions.h"

typedef sf::Vector2f vec2;

class Player : public Entity
{
public:
	vec2 mMousePos					 = vec2(0.0f, 0.0f);
	vec2 mFacingDir					 = vec2(0.0f, 0.0f);
	// Bullet variables
	const float mBulletFireDelay     = 0.2f;
	float mBulletFireCooldown	     = 0.0f;
	float mBulletLifeSpan		     = 2.5f;
	int mBulletsFiredLimit			 = 3;
	bool mFiredRecently				 = false;

	//////////////////////////////////////////////////////////////////////////////

	virtual void Update(std::vector<Bullet> &bullets, float dt);

	void DetectCollisions(std::vector<Obstacle*> obstacles, float dt, vec2 winSize);

	void CheckAgainstWindow(vec2 winSize);
	
	void CheckAgainstCircleObstacle(CircleObstacle* circleObs, float dt);
	
	void CheckAgainstRectangleObstacle(RectangleObstacle* rectObs, float dt);
	
	void Render(sf::RenderWindow* renderWin, Resources* resources);
};