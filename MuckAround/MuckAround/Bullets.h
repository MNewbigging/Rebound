#pragma once

//#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Entity.h"
#include "Obstacles.h"
#include "HelperFunctions.h"


typedef sf::Vector2f vec2;

class Bullet : public Entity
{
public:
	// Has bullet been fired
	bool mActive = false;
	// Has bullet collided with surface
	bool mCanDamage = false;
	// Off screen position whilst inactive
	vec2 mBulletPoolPos = vec2(0.0f, 0.0f);
	// Bullet decay
	float mLifetime = 0.0f;
	// Bullet damage
	float mDamage = 25.0f;
	// Enforce cooldown on rebounding (so as not to proc col res more than once per bounce)
	float mBounceCooldown = 0.0f;
	float mMaxBounceCooldown = 0.1f;
	//////////////////////////////////////////////////////////////////////////////
	Bullet() {}
	~Bullet() {}

	void Update(float dt);

	void MoveToBulletPool();

	void DetectCollisions(std::vector<Obstacle*> obstacles, vec2 winSize);
	
	void CheckAgainstWindow(vec2 winSize);
	
	void CheckAgainstCircleObstacle(CircleObstacle* circleObs);
	
	void CheckAgainstRectangleObstacle(RectangleObstacle* rectObs);

	void Render(sf::RenderWindow* renderWin);
};