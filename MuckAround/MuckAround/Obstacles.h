#pragma once

#include <SFML\Graphics.hpp>

typedef sf::Vector2f vec2;

class Obstacle
{
public:

	sf::IntRect mRectangle;

	vec2 mPos		= vec2(0.0f, 0.0f);
	vec2 mSize	    = vec2(0.0f, 0.0f);

	sf::Color mColour = sf::Color::White;

	void Render(sf::RenderWindow* renderWin)
	{
		sf::RectangleShape rectShape(mSize);

		rectShape.setFillColor(mColour);

		rectShape.setOrigin(mSize / 2.0f);

		rectShape.setPosition(mPos);

		renderWin->draw(rectShape);
	}
};