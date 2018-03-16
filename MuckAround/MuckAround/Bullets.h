#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"

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

	void Render(sf::RenderWindow* renderWin)
	{
		sf::CircleShape bulletCircle(10.0f);
		bulletCircle.setOrigin(5.0f, 5.0f);
		bulletCircle.setPosition(mPos);
		renderWin->draw(bulletCircle);	
	}

	
};