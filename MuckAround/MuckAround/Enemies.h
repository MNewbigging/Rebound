#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"

typedef sf::Vector2f vec2;

class BasicEnemy : public Entity
{
public:
	
	float mLastHit = 0.0f;

	sf::Color color = sf::Color::Red;

	void Update()
	{
		
	}

	void Render()
	{

	}
};