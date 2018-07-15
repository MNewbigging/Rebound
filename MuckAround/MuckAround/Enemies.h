#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "EnemyWaveSystem.h"


typedef sf::Vector2f vec2;

class Enemy : public Entity
{
public:
	vec2 mEnemyPoolPos  = vec2(0.0f, 0.0f);

	bool mActive		= false;

	sf::Color mColor;
	sf::Color mNormalColor;
	sf::Color mHitColor;

	//////////////////////////////////////////////////////////////////////////////

	// Track player
	void Update(vec2 playerPos, float dt)
	{
		if (mActive)
		{
			// Move towards player
			mVelocity = Normalize(playerPos - mPos) * mSpeed;
			mPos += mVelocity * dt;

			// Change color back to normal
			mColor = mNormalColor;
		}
	}

	// On enemy death
	void MoveToEnemyPool()
	{
		mPos = mEnemyPoolPos;
		mHealth = mMaxHealth;
		mActive = false;
	}

	void DetectCollisions(std::vector<Enemy> enemies, std::vector<Obstacle*> obstacles, std::vector<Bullet> &bullets, float dt)
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
				CheckAgainstCircleObstacle(circleObs, dt);
				break;
			}
			// Rectangle obstacle
			case 2:
			{
				// Cast obs to rectangle type
				RectangleObstacle* rectObs = dynamic_cast<RectangleObstacle*>(obs);
				CheckAgainstRectangleObstacle(rectObs, dt);
				break;
			}
				
			default:
				break;
			}
			
		}

		// Check against bullets
		CheckAgainstBullets(bullets); 

		// Check againt other enemies
		CheckAgainstEnemies(enemies, dt);
	}

	void CheckAgainstCircleObstacle(CircleObstacle* circleObs, float dt)
	{
		if (CircleToCircleIntersection(mPos, circleObs->mPos, mRadius, circleObs->mRadius))
		{
			// Find collision normal
			vec2 colNormal = Normalize(circleObs->mPos - mPos);
			// Move back based on normal by speed
			mPos -= colNormal * mSpeed * dt;
		}
	}
		
	void CheckAgainstRectangleObstacle(RectangleObstacle* rectObs, float dt)
	{
		// Basic distance check - only perform actual collision checks if close enough
		vec2 d = rectObs->mPos - mPos;
		if (LengthSq(d) < 2 * LengthSq(rectObs->mSize))
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
						// Move enemy back along collision normal
						mPos -= colNormal * mSpeed * dt;
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
					// Move enemy back along collision normal
					mPos -= colNormal * mSpeed * dt;
				}
			}

		}
	}

	void CheckAgainstBullets(std::vector<Bullet> &bullets)
	{
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
				b.MoveToBulletPool();
				// Has this enemy died? 
				if (mHealth <= 0)
				{
					MoveToEnemyPool();
				}
			}
		}
	}
	
	void CheckAgainstEnemies(std::vector<Enemy> enemies, float dt)
	{
		for (auto &e : enemies)
		{
			if (e.mPos != mPos)
			{
				if (CircleToCircleIntersection(mPos, e.mPos, mRadius, e.mRadius))
				{
					// Find collision normal
					vec2 colNormal = Normalize(e.mPos - mPos);
					// Move back based on normal by speed
					mPos -= colNormal * mSpeed * dt;
				}
			}
		}
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