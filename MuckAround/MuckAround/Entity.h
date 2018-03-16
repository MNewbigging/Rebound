#pragma once

#include <SFML\Graphics.hpp>

typedef sf::Vector2f vec2;

class Entity
{
public:

	vec2 mPos		 = vec2(0.0f, 0.0f);
	vec2 mVelocity   = vec2(0.0f, 0.0f);

	float mHealth    = 0.0f;
	float mSpeed     = 0.0f;
	float mRadius	 = 0.0f;

	virtual void Update() {}
	virtual void Render() {}

};