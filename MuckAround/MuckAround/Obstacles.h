#pragma once

#include <SFML\Graphics.hpp>

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
	virtual void Render(sf::RenderWindow* renderWin)
	{
		
	}
};
