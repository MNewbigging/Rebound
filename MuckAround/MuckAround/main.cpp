// MuckAround.cpp : Defines the entry point for the console application.
//


#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Resources.h"
#include "Gamestate.h"


using namespace std;

typedef sf::Vector2f vec2;

const vec2 sWindowSize = vec2(1280.0f, 720.0f);

///////////////////////////////////////////////////////////////////

void Update(Gamestate* gameState, float dt)
{
	// Update player
	gameState->mPlayer.Update(gameState->mBullets, dt);
	// Check for player collisions
	gameState->mPlayer.DetectCollisions(gameState->mObstacles, dt, sWindowSize);

	// Update bullets
	for (auto &b : gameState->mBullets)
	{
		b.Update(dt);
		// Apply collision detection/response
		b.DetectCollisions(gameState->mObstacles, sWindowSize);
	}

	// Update enemies
	for (auto &e : gameState->mEnemies)
	{
		e.Update(gameState->mPlayer.mPos, dt);
		e.DetectCollisions(gameState->mEnemies, gameState->mObstacles, gameState->mBullets, dt);
	}

	// Update systems
	gameState->systemManager.Update(gameState->mEnemies, dt);

}

///////////////////////////////////////////////////////////////////

void Render(Gamestate* gameState, sf::RenderWindow* renderWin, Resources* resources)
{
	// Render player
	gameState->mPlayer.Render(renderWin, resources);
	// Render bullets
	for (auto b : gameState->mBullets)
	{
		b.Render(renderWin);
	}
	// Render obstacles
	for (auto o : gameState->mObstacles)
	{
		o->Render(renderWin);
	}
	// Render basic enemies
	for (auto e : gameState->mEnemies)
	{
		e.Render(renderWin);
	}
}

///////////////////////////////////////////////////////////////////

int main()
{
	// Create the game window
	sf::RenderWindow window(sf::VideoMode((uint32_t)sWindowSize.x, (uint32_t)sWindowSize.y), "Rebound");
	window.setVerticalSyncEnabled(true);
	
	// This sets origin to center of screen
	sf::View view(vec2(0.0f, 0.0f), sWindowSize);
	window.setView(view);

	// Tracks time between frames (dt)
	sf::Clock clock;

	// Initialise gamestate
	Gamestate gameState = {};
	
	// Setup game vars
	gameState.SetupGame(sWindowSize);

	// Setup resources
	Resources resources;
	if (!resources.LoadResources())
	{
		cout << "Failed to load resources!\n";

		return -1;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Calculate dt
		sf::Time frameTime = clock.getElapsedTime();
		clock.restart();

		window.clear();
		
		// Update mouse position
		gameState.mPlayer.mMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		// Update entities
		Update(&gameState, frameTime.asSeconds());

		// Render entities
		Render(&gameState, &window, &resources);


		window.display();


	}


	// Keep console window open
	getchar();
	return 0;
}

