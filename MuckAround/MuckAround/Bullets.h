#pragma once

#include <SFML\Graphics.hpp>
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
	bool mActive	     = false;
	// Has bullet collided with surface
	bool mCanDamage		 = false;
	// Off screen position whilst inactive
	vec2 mBulletPoolPos  = vec2(0.0f, 0.0f);


	// Bullet decay
	float mLifetime				= 0.0f;
	
	int count = 0;

	// Since using bullet pool; when not fired/alive move off screen and reset
	void MoveToBulletPool()
	{
		mPos = mBulletPoolPos;
		mActive = false;
		mCanDamage = false;
	}

	// Update position, reset to bullet pool if life ended
	void Update(float dt)
	{
		// Is this bullet active (fired from player and on screen?)
		if (mActive)
		{
			// Reduce lifetime
			mLifetime -= dt;

			// If bullet has decayed, reset it
			if (mLifetime <= 0.0f)
			{
				MoveToBulletPool();
			}
			else
			{
				// Calculate next position of bullet
				mPos += mVelocity * dt;

			}
		}
		// Otherwise this bullet is inactive, keep it off screen
		else
		{
			MoveToBulletPool();
		}

	}

	// Draw to window
	void Render(sf::RenderWindow* renderWin)
	{
		sf::CircleShape bulletCircle(mRadius);
		bulletCircle.setOrigin(mRadius / 2, mRadius / 2);
		bulletCircle.setPosition(mPos);
		renderWin->draw(bulletCircle);	
	}
	
	// Obstacles, window edges
	void DetectCollisions(std::vector<Obstacle> obstacles, vec2 winSize, float dt)
	{
		// Only test for cols if bullet is active
		if (mActive)
		{
			// Test against obstacles
			for (auto &obs : obstacles)
			{
				if (CircleToCircleIntersection(mPos, obs.mPos, mRadius, obs.mRadius))
				{
					// Find collision normal
					vec2 colNormal = Normalize(obs.mPos - mPos);
					// Reflect around this normal
					mVelocity = Reflect(mVelocity, colNormal);
				}
			}

			// Test against edge of screen (should bounce inwards as if there was a wall)
			if (mPos.x + mRadius > winSize.x / 2)
			{
				// Move away from collision point
				mPos.x = (winSize.x / 2) - mRadius;
				// Normal points to left
				vec2 colNormal = vec2(-1.0f, 0.0f);
				// Reflect
				mVelocity = Reflect(mVelocity, colNormal);
			}
			else if (mPos.x - mRadius < -(winSize.x / 2))
			{
				// Move away from collision
				mPos.x = -(winSize.x / 2) + mRadius;
				// Normal points to right
				vec2 colNormal = vec2(1.0f, 0.0f);
				// Reflect
				mVelocity = Reflect(mVelocity, colNormal);
			}
			// Again for y
			if (mPos.y + mRadius > winSize.y / 2)
			{
				mPos.y = (winSize.y / 2) - mRadius;
				vec2 colNormal = vec2(0.0f, 1.0f);
				mVelocity = Reflect(mVelocity, colNormal);
			}
			else if (mPos.y - mRadius < -(winSize.y / 2))
			{
				mPos.y = -(winSize.y / 2) + mRadius;
				vec2 colNormal = vec2(0.0f, -1.0f);
				mVelocity = Reflect(mVelocity, colNormal);
			}
		}
		

	}


};