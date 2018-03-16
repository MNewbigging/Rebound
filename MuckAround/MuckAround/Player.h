#pragma once

#include <SFML\Graphics.hpp>

#include "Entity.h"
#include "HelperFunctions.h"

typedef sf::Vector2f vec2;

class Player : public Entity
{
public:
	vec2 mMousePos  = vec2(0.0f, 0.0f);
	vec2 mFacingDir = vec2(0.0f, 0.0f);
	

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