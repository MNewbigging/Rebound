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
	bool mActive;
	// Has bullet collided with surface
	bool mCanDamage;
	// Off screen position whilst inactive
	vec2 mBulletPoolPos;
	// Bullet decay
	float mLifetime;
	// Bullet damage
	float mDamage;
	// Enforce cooldown on rebounding (so as not to proc col res more than once per bounce)
	float mBounceCooldown;
	float mMaxBounceCooldown;
	//////////////////////////////////////////////////////////////////////////////
	Bullet();
	~Bullet() {}

	void Update(float dt);

	void MoveToBulletPool();

	void DetectCollisions(std::vector<Obstacle*> obstacles, vec2 winSize);
	
	void CheckAgainstWindow(vec2 winSize);
	
	void CheckAgainstCircleObstacle(CircleObstacle* circleObs);
	
	void CheckAgainstRectangleObstacle(RectangleObstacle* rectObs);

	void Render(sf::RenderWindow* renderWin);
};