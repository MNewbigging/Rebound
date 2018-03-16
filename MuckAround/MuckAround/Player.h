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
	float mBulletFireCooldown	     = 0.0f;
	const float mBulletFireDelay     = 0.1f;
	int mBulletsFiredLimit			 = 3;
	int mBulletsFiredCurrently		 = 0;
	float mBulletLifeSpan			 = 1.5f;
	bool mFiredRecently				 = false;

	std::vector<Bullet> mBullets;

	// Use bullet pool to avoid new/delete operations at runtime
	void SetupBullets(vec2 offScreenPos, int maxBulletCount, float bulletSize, float bulletSpeed)
	{
		for (int i = 0; i < maxBulletCount; i++)
		{
			//Entity *bptr;
			Bullet bullet;
			//bptr = &bullet;

			// Make sure to spread out each bullet - each has unqiue place to reset to
			bullet.mBulletPoolPos = vec2(offScreenPos.x + (i * bulletSize * 2), offScreenPos.y);
			// Set default bullet speed
			bullet.mSpeed = bulletSpeed;
			// Set radius
			bullet.mRadius = bulletSize;
			// Add to pool
			mBullets.push_back(bullet);
		}

		std::cout << " ";
	}

	void Update(float dt)
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
				// And there are bullets available to fire
				if (mBulletsFiredCurrently < mBulletsFiredLimit)
				{
					// Reset cooldown timer to prevent firing again immediately
					mBulletFireCooldown = mBulletFireDelay;

					// Activate the next available bullet
					mBullets[mBulletsFiredCurrently].mActive = true;
					
					// Set movement vars
					mBullets[mBulletsFiredCurrently].mLifetime = mBulletLifeSpan;
					mBullets[mBulletsFiredCurrently].mPos = mPos;
					mBullets[mBulletsFiredCurrently].mVelocity = mFacingDir * mBullets[mBulletsFiredCurrently].mSpeed; // Store bullet speed in player? 
					

				}
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