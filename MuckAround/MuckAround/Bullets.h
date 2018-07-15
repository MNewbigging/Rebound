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
	float mLifetime		 = 0.0f;
	// Bullet damage
	float mDamage		 = 25.0f;
	// Enforce cooldown on rebounding (so as not to proc col res more than once per bounce)
	float mCanBounce	  = 0.0f;
	float mBounceCooldown = 0.1f;
	//////////////////////////////////////////////////////////////////////////////

	// Update position, reset to bullet pool if life ended
	void Update(float dt)
	{
		// Is this bullet active (fired from player and on screen?)
		if (mActive)
		{
			// Reduce can bounce cooldown
			mCanBounce -= dt;
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
				mPos += mVelocity * mSpeed * dt;
			}
		}
	}

	// Since using bullet pool; when not fired/alive move off screen and reset
	void MoveToBulletPool()
	{
		mPos = mBulletPoolPos;
		mActive = false;
		mCanDamage = false;
	}
	
	void DetectCollisions(std::vector<Obstacle*> obstacles, vec2 winSize)
	{
		// Only test for cols if bullet is active
		if (mActive)
		{
			// Check against window edges
			CheckAgainstWindow(winSize);

			// Test against obstacles
			for (auto &obs : obstacles)
			{
				// Actions depend on this obstacle's derived type
				switch (obs->mType)
				{
				// Circle obstacle
				case 1:
				{
					// Cast obs to circle type
					CircleObstacle* circleObs = dynamic_cast<CircleObstacle*>(obs);
					CheckAgainstCircleObstacle(circleObs);
					break;
				}
				// Rectangle obstacle
				case 2:
				{
					// Cast obs to rect type
					RectangleObstacle* rectObs = dynamic_cast<RectangleObstacle*>(obs);
					CheckAgainstRectangleObstacle(rectObs);
					break;
				}
				default:
					break;
				} // end switch
			} // end for each obstacle		
		} // end if active
	} // end detect cols

	void CheckAgainstWindow(vec2 winSize)
	{
		// Test against edge of screen (should bounce inwards as if there was a wall)
		if (mPos.x + mRadius > winSize.x / 2)
		{
			// Move away from collision point
			mPos.x = (winSize.x / 2) - mRadius;
			// Normal points to left
			vec2 colNormal = vec2(-1.0f, 0.0f);
			// Reflect
			mVelocity = Reflect(mVelocity, colNormal);
			// Bullet has collided with something
			mCanDamage = true;
		}
		else if (mPos.x - mRadius < -(winSize.x / 2))
		{
			// Move away from collision
			mPos.x = -(winSize.x / 2) + mRadius;
			// Normal points to right
			vec2 colNormal = vec2(1.0f, 0.0f);
			// Reflect
			mVelocity = Reflect(mVelocity, colNormal);
			// Bullet has collided with something
			mCanDamage = true;
		}
		// Again for y
		if (mPos.y + mRadius > winSize.y / 2)
		{
			mPos.y = (winSize.y / 2) - mRadius;
			vec2 colNormal = vec2(0.0f, 1.0f);
			mVelocity = Reflect(mVelocity, colNormal);
			// Bullet has collided with something
			mCanDamage = true;
		}
		else if (mPos.y - mRadius < -(winSize.y / 2))
		{
			mPos.y = -(winSize.y / 2) + mRadius;
			vec2 colNormal = vec2(0.0f, -1.0f);
			mVelocity = Reflect(mVelocity, colNormal);
			// Bullet has collided with something
			mCanDamage = true;
		}
	}

	void CheckAgainstCircleObstacle(CircleObstacle* circleObs)
	{
		if (CircleToCircleIntersection(mPos, circleObs->mPos, mRadius, circleObs->mRadius)
			&& mCanBounce <= 0)
		{
			// Find collision normal
			vec2 colNormal = Normalize(circleObs->mPos - mPos);
			// Reflect around this normal
			mVelocity = Reflect(mVelocity, colNormal);
			// Bullet has collided with something
			mCanDamage = true;
			// Set bounce timer
			mCanBounce = mBounceCooldown;
		}
	}

	void CheckAgainstRectangleObstacle(RectangleObstacle* rectObs)
	{
		// Basic distance check - only perform actual collision checks if close enough
		vec2 d = rectObs->mPos - mPos;
		if (LengthSq(d) < 2 * LengthSq(rectObs->mSize) && mCanBounce <= 0)
		{
			// Iterate over rect vertices to find which side might be intersecting player 
			for (int i = 0; i < (int)rectObs->mVertices.size(); i++)
			{
				// Find the closest point on line to circle (if there's an intersection)
				vec2 point = vec2(0.0f, 0.0f);
				// Wrap around: 3-0
				if (i == 3)
				{
					if (LineToCircleIntersection(rectObs->mVertices[i],
						rectObs->mVertices[0],
						mPos, mRadius,
						point))
					{
						// Find collision normal
						vec2 colNormal = Normalize(point - mPos);
						// Reflect around this normal
						mVelocity = Reflect(mVelocity, colNormal);
						// Bullet has collided with something
						mCanDamage = true;
						// Reset bounce cooldown
						mCanBounce = mBounceCooldown;
					}
					break;
				}
				// 0-1, 1-2, 2-3
				if (LineToCircleIntersection(rectObs->mVertices[i],
					rectObs->mVertices[i + 1],
					mPos, mRadius,
					point))
				{
					// Find collision normal
					vec2 colNormal = Normalize(point - mPos);
					// Reflect around this normal
					mVelocity = Reflect(mVelocity, colNormal);
					// Bullet has collided with something
					mCanDamage = true;
					// Reset bounce cooldown
					mCanBounce = mBounceCooldown;
					break;
				}
			}

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

};