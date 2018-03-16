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
	float mBulletFireCooldown	     = 0.0f;
	const float mBulletFireDelay     = 0.2f;
	int mBulletsFiredLimit			 = 3;
	float mBulletLifeSpan			 = 2.5f;
	bool mFiredRecently				 = false;

	



	void Update(std::vector<Bullet> &bullets, float dt)
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

						// Activate the next available bullet
						bullets[i].mActive = true;

						// Set movement vars
						bullets[i].mLifetime = mBulletLifeSpan;
						bullets[i].mPos = mPos;
						bullets[i].mVelocity = mFacingDir * bullets[i].mSpeed; // Store bullet speed in player? 

						// Stop looking for other active bullets
						break;
					}
					// else - no bullets available (sfx?)
				}
			}
		} // end if mouse left down
	
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