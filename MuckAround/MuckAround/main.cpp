// MuckAround.cpp : Defines the entry point for the console application.
//


#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Resources.h"
#include "Gamestate.h"


using namespace std;

typedef sf::Vector2f vec2;



///////////////////////////////////////////////////////////////////

void Update(Gamestate* gameState, float dt)
{
	// Update player
	gameState->mPlayer.Update(gameState->mBullets, dt);
	// Update bullets
	for (auto &b : gameState->mBullets)
	{
		b.Update(dt);
	}
}

///////////////////////////////////////////////////////////////////

void Render(Gamestate* gameState, sf::RenderWindow* renderWin, Resources* resources)
{
	// Render player
	gameState->mPlayer.Render(renderWin, resources);
	// Render bullets
	for (auto &b : gameState->mBullets)
	{
		b.Render(renderWin);
	}
}

///////////////////////////////////////////////////////////////////

int main()
{
	vec2 windowSize = vec2(1280.0f, 720.0f);


	sf::RenderWindow window(sf::VideoMode((uint32_t)windowSize.x, (uint32_t)windowSize.y), "Bouncy Bullets");
	window.setVerticalSyncEnabled(true);
	
	// This sets origin to center of screen
	sf::View view(vec2(0.0f, 0.0f), windowSize);
	window.setView(view);

	// Tracks time between frames (dt)
	sf::Clock clock;

	// Initiate gamestate
	Gamestate gameState = {};
	
	// Setup game vars
	gameState.SetupGame(windowSize);
	

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

