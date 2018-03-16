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
		sf::CircleShape bulletCircle(10.0f);
		bulletCircle.setOrigin(5.0f, 5.0f);
		bulletCircle.setPosition(mPos);
		renderWin->draw(bulletCircle);	
	}
	
	
	void DetectCollisions(std::vector<Obstacle> obstacles, float dt)
	{
		// Print to console if rectangle was hit
		for (auto obs : obstacles)
		{
			// Int rects start top left, obs has central origin
			vec2 pos = vec2(obs.mPos.x - (obs.mSize.x / 2.0f), obs.mPos.y - (obs.mSize.y / 2.0f));
			sf::IntRect r(pos.x, pos.y, obs.mSize.x, obs.mSize.y);


			// TODO - check with point radius length away down dir vector			
			if (r.contains((int)mPos.x, (int)mPos.y))
			{
				std::cout << " bullets hit" << std::endl;
				
				// Find collision normal
				vec2 colNormal = Normalize(obs.mPos - mPos);

				mVelocity = Reflect(mVelocity, colNormal);

				mPos += mVelocity * dt;

			}
		}
	}


};