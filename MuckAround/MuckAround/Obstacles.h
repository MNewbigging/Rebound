#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
//#include "HelperFunctions.h"

typedef sf::Vector2f vec2;

class Obstacle
{
public:

	int mType;

	vec2 mPos;
	
	sf::Color mColour;

	virtual void Render(sf::RenderWindow* renderWin) = 0;
};

class CircleObstacle : public Obstacle
{
public:

	float mRadius = 0.0f;

	/////////////////////////////////////////////////////////////////////

	virtual void Render(sf::RenderWindow* renderWin);
	
};

class RectangleObstacle : public Obstacle
{
public:
	
	float mRot = 0.0f;

	vec2 mSize = vec2(0.0f, 0.0f);

	std::vector<vec2> mVertices;

	bool goingLeft = false;

	float mSpeed = 15.0f;

	/////////////////////////////////////////////////////////////////////

	void Update(float dt, vec2 winSize);

	void FindVertices();
	
	virtual void Render(sf::RenderWindow* renderWin);

};
