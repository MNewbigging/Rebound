#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

typedef sf::Vector2f vec2;

class Obstacle
{
public:

	int mType;

	vec2 mPos		    = vec2(0.0f, 0.0f);
	
	sf::Color mColour;

	virtual void Render(sf::RenderWindow* renderWin) = 0;
};

class CircleObstacle : public Obstacle
{
public:

	float mRadius = 0.0f;

	/////////////////////////////////////////////////////////////////////

	virtual void Render(sf::RenderWindow* renderWin)
	{
		
		sf::CircleShape circleShape(mRadius);

		circleShape.setFillColor(mColour);

		circleShape.setOrigin(mRadius, mRadius);

		circleShape.setPosition(mPos);

		renderWin->draw(circleShape);
	}
};

class RectangleObstacle : public Obstacle
{
public:

	vec2 mSize = vec2(0.0f, 0.0f);

	std::vector<vec2> mVertices;

	/////////////////////////////////////////////////////////////////////

	// Determine & cache vertices of this rectangle
	void FindVertices()
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
	}
	
	virtual void Render(sf::RenderWindow* renderWin)
	{
		sf::RectangleShape rectShape(mSize);

		rectShape.setFillColor(mColour);

		rectShape.setOrigin(mSize * 0.5f);

		rectShape.setPosition(mPos);

		renderWin->draw(rectShape);
	}
};
