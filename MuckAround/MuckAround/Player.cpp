#include "Player.h"

using namespace HelperFunctions;
// Handles movement, firing bullets
// TODO - separate into more functions
void Player::Update(std::vector<Bullet> &bullets, float dt)
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
					bullets[i].mVelocity = mFacingDir; // Store bullet speed in player? 

													   // Stop looking for other active bullets
					break;
				}
			}
		}
	} // end if mouse left down

}

void Player::DetectCollisions(std::vector<Obstacle*> obstacles, float dt, vec2 winSize)
{
	// Check agaist game window
	CheckAgainstWindow(winSize);

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
			// Cast obs to rect type
			RectangleObstacle* rectObs = dynamic_cast<RectangleObstacle*>(obs);
			CheckAgainstRectangleObstacle(rectObs, dt);
			break;
		} // case 2 end

		default:
			break;
		} // switch end

	}
}

void Player::CheckAgainstWindow(vec2 winSize)
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
}

void Player::CheckAgainstCircleObstacle(CircleObstacle* circleObs, float dt)
{
	if (CircleToCircleIntersection(mPos, circleObs->mPos, mRadius, circleObs->mRadius))
	{
		// Find collision normal
		vec2 colNormal = Normalize(circleObs->mPos - mPos);
		// Move back based on normal by speed
		// Essentially the reverse of how we got here
		mPos -= colNormal * mSpeed * dt;
	}
}

void Player::CheckAgainstRectangleObstacle(RectangleObstacle* rectObs, float dt)
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
					// Move player back along collision normal
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
				// Move player back along collision normal
				mPos -= colNormal * mSpeed * dt;
			}
		}

	}
}

void Player::Render(sf::RenderWindow* renderWin, Resources* resources)
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













