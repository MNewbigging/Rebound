#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"

typedef sf::Vector2f vec2;

class BasicEnemy : public Entity
{
public:
	
	float mLastHit		= 0.0f;
	vec2 mEnemyPoolPos  = vec2(0.0f, 0.0f);

	sf::Color mColor;
	sf::Color mNormalColor;
	sf::Color mHitColor;

	// Track player
	void Update(vec2 playerPos, float dt)
	{
		// Move towards player
		mVelocity = Normalize(playerPos - mPos) * mSpeed;
		mPos += mVelocity * dt;

		// Change color back to normal
		mColor = mNormalColor;
	}


	void DetectCollisions(std::vector<Obstacle*> obstacles, std::vector<Bullet> &bullets, float dt)
	{
		// Check against obstacles
		for (auto &obs : obstacles)
		{
			switch (obs->mType)
			{
			// Circle obstacle
			case 1:
			{
				// Cast obs to circle type
				CircleObstacle* circleObs = dynamic_cast<CircleObstacle*>(obs);
				if (CircleToCircleIntersection(mPos, circleObs->mPos, mRadius, circleObs->mRadius))
				{
					// Find collision normal
					vec2 colNormal = Normalize(circleObs->mPos - mPos);
					// Move back based on normal by speed
					mPos -= colNormal * mSpeed * dt;
				}
			}
			default:
				break;
			}
			
		}

		// Check against bullets
		for (auto &b : bullets)
		{
			if (b.mCanDamage && CircleToCircleIntersection(mPos, b.mPos, mRadius, b.mRadius))
			{
				// Remove as much health as bullet damage
				mHealth -= b.mDamage;
				// Flash color to show hit effect
				mColor = mHitColor;
				// Send bullet back to pool
				//b.MoveToBulletPool();
				b.mPos = b.mBulletPoolPos;
				b.mActive = false;
				b.mCanDamage = false;
				// Has this enemy died? 
				if (mHealth <= 0)
				{
					MoveToEnemyPool();
				}
			}
		}
	}

	void MoveToEnemyPool()
	{
		mPos = mEnemyPoolPos;
		mHealth = mMaxHealth;
	}

	void Render(sf::RenderWindow* renderWin)
	{
		sf::CircleShape circleShape(mRadius);

		circleShape.setFillColor(mColor);

		circleShape.setOrigin(mRadius, mRadius);

		circleShape.setPosition(mPos);

		renderWin->draw(circleShape);
	}

};