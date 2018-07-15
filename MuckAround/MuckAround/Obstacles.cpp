#include "Obstacles.h"

CircleObstacle::CircleObstacle()
{
	mType = 1;
}

void CircleObstacle::Render(sf::RenderWindow* renderWin)
{

	sf::CircleShape circleShape(mRadius);

	circleShape.setFillColor(mColour);

	circleShape.setOrigin(mRadius, mRadius);

	circleShape.setPosition(mPos);

	renderWin->draw(circleShape);
}

/////////////////////////////////////////////////////////////////////

RectangleObstacle::RectangleObstacle()
{
	mType = 2;
}

void RectangleObstacle::Update(float dt, vec2 winSize)
{
	if (mPos.x >= (winSize.x + mSize.x) * 0.5f)
		goingLeft = true;

	else if (mPos.x <= -(winSize.x + mSize.x) * 0.5f)
		goingLeft = false;

	if (goingLeft)
		mPos.x -= mSpeed * dt;
	else
		mPos.x += mSpeed * dt;

	FindVertices();
}

void RectangleObstacle::FindVertices()
{
	// ! Origin is in center of rect
	// Top left is first vertex
	vec2 vA = mPos - (mSize * 0.5f);
	// Top right
	vec2 vB = vec2(0.0f, 0.0f);
	vB.x = mPos.x + (mSize.x * 0.5f);
	vB.y = mPos.y - (mSize.y * 0.5f);
	// Bottom right
	vec2 vC = mPos + (mSize * 0.5f);
	// Bottom left
	vec2 vD = vec2(0.0f, 0.0f);
	vD.x = mPos.x - (mSize.x * 0.5f);
	vD.y = mPos.y + (mSize.y * 0.5f);

	// Update vertices list
	mVertices.clear();
	mVertices.push_back(vA);
	mVertices.push_back(vB);
	mVertices.push_back(vC);
	mVertices.push_back(vD);

	// Apply rotation of rect to each corner point
	for (auto &v : mVertices)
	{
		// Translate corner point to origin
		float transX = v.x - mPos.x;
		float transY = v.y - mPos.y;
		// Apply rotation
		float rotatedX = (transX * cos(mRot)) - (transY * sin(mRot));
		float rotatedY = (transX * sin(mRot)) + (transY * cos(mRot));
		// Translate back to corner point
		v.x = rotatedX + mPos.x;
		v.y = rotatedY + mPos.y;
	}
}

void RectangleObstacle::Render(sf::RenderWindow* renderWin)
{
	sf::RectangleShape rectShape(mSize);

	rectShape.setFillColor(mColour);

	rectShape.setOrigin(mSize * 0.5f);

	rectShape.setPosition(mPos);

	rectShape.setRotation(mRot);

	renderWin->draw(rectShape);
}

