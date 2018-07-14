#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "Entity.h"
#include "Bullets.h"
#include "HelperFunctions.h"

typedef sf::Vector2f vec2;

class Player : public Entity
{
public:
	vec2 mMousePos					 = vec2(0.0f, 0.0f);
	vec2 mFacingDir					 = vec2(0.0f, 0.0f);
	// Bullet variables
	const float mBulletFireDelay = 0.2f;
	float mBulletFireCooldown	     = 0.0f;
	float mBulletLifeSpan		     = 2.5f;
	int mBulletsFiredLimit			 = 3;
	bool mFiredRecently				 = false;

	//////////////////////////////////////////////////////////////////////////////

	// Handles movement, firing bullets
	virtual void Update(std::vector<Bullet> &bullets, float dt)
	{
		mVelocity = vec2(0.0f, 0.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			mVelocity.y -= 1.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mVelocity.y += 1.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			mVelocity.x += 1.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			mVelocity.x -= 1.0f;
		}

		// Ensure the player doesn't go faster diagonally
		if (LengthSq(mVelocity) > 1.0f)
		{
			mVelocity = Normalize(mVelocity);
		}

		// Update position based on velocity, speed, delta time
		mPos += mVelocity * mSpeed * dt;

		// Rotate player to face mouse
		vec2 playerToMouse = mMousePos - mPos;
		mFacingDir = Normalize(playerToMouse);

		// Firing
		mBulletFireCooldown -= dt;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// If cooldown allows another bullet to be fired
			if (mBulletFireCooldown <= 0.0f)
			{
				// Loop through bullets to find one available to fire
				for (int i = 0; i < mBulletsFiredLimit; i++)
				{
					// Look for inactive bullet to fire - if there aren't any then nothing will happen
					if (!bullets[i].mActive)
					{
						// Reset cooldown timer to prevent firing again immediately
						mBulletFireCooldown = mBulletFireDelay;

						// Activate this available bullet
						bullets[i].mActive = true;

						// Set movement vars
						bullets[i].mLifetime = mBulletLifeSpan;
						bullets[i].mPos = mPos;
						bullets[i].mVelocity = mFacingDir * bullets[i].mSpeed; // Store bullet speed in player? 

						// Stop looking for other active bullets
						break;
					}
				}
			}
		} // end if mouse left down
	
	}


	void DetectCollisions(std::vector<Obstacle*> obstacles, float dt, vec2 winSize)
	{
		// Check against window boundaries
		if (mPos.x + mRadius > winSize.x * 0.5f)
		{
			// Move back within window
			mPos.x = (winSize.x * 0.5f) - mRadius;
		}
		else if (mPos.x - mRadius < -(winSize.x * 0.5f))
		{
			mPos.x = -(winSize.x * 0.5f) + mRadius;
		}
		if (mPos.y + mRadius > winSize.y * 0.5f)
		{
			mPos.y = (winSize.y * 0.5f) - mRadius;
		}
		else if (mPos.y - mRadius < -(winSize.y * 0.5f))
		{
			mPos.y = -(winSize.y * 0.5f) + mRadius;
		}

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
					// Essentially the reverse of how we got here
					mPos -= colNormal * mSpeed * dt;
				}
				break;
			}
			default:
				break;
			}
			
		}
	}

	void Render(sf::RenderWindow* renderWin, Resources* resources)
	{
		// Grab player sprite texture from resources
		sf::Sprite playerSprite(resources->mPlayerTex);

		// Set origin to center (move by half width/height of texture)
		playerSprite.setOrigin((vec2)resources->mPlayerTex.getSize() * 0.5f);

		// Set position
		playerSprite.setPosition(mPos);
		
		// Set rotation
		playerSprite.setRotation(RadiansToDegrees(ToAngle(mFacingDir)));

		// Draw
		renderWin->draw(playerSprite);
	}
};