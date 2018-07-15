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

	float mRadius;

	/////////////////////////////////////////////////////////////////////
	CircleObstacle();
	~CircleObstacle() {}

	virtual void Render(sf::RenderWindow* renderWin);
	
};

class RectangleObstacle : public Obstacle
{
public:
	
	float mRot;

	vec2 mSize;

	std::vector<vec2> mVertices;

	bool goingLeft;

	float speed;

	/////////////////////////////////////////////////////////////////////
	RectangleObstacle();
	~RectangleObstacle() {}

	void Update(float dt, vec2 winSize);

	void FindVertices();
	
	virtual void Render(sf::RenderWindow* renderWin);

};
