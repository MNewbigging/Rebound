#pragma once

#include <SFML\Graphics.hpp>

#include "Player.h"

typedef sf::Vector2f vec2;

struct Gamestate
{
	vec2 mMousePos = vec2(0.0f, 0.0f);

	Player mPlayer;

	//vector<Entity*> mEnemies;
    //vector<Entity*> mBullets;
};