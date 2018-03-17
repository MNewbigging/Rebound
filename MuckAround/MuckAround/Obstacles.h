#pragma once

#include <SFML\Graphics.hpp>

typedef sf::Vector2f vec2;

class Obstacle
{
public:

	vec2 mPos		= vec2(0.0f, 0.0f);
	
	float mRadius	= 0.0f;

	sf::Color mColour;

	void Render(sf::RenderWindow* renderWin)
	{
		
		sf::CircleShape circleShape(mRadius);

		circleShape.setFillColor(mColour);

		circleShape.setOrigin(mRadius, mRadius);

		circleShape.setPosition(mPos);

		renderWin->draw(circleShape);

	}
};