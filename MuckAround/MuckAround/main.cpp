// MuckAround.cpp : Defines the entry point for the console application.
//


#include <SFML/Graphics.hpp>
#include <vector>


#include "Entity.h"
#include "Enemies.h"
#include "Player.h"


using namespace std;

typedef sf::Vector2f vec2;

struct Gamestate
{
	Player mPlayer;

	vector<Entity*> mEnemies;
	vector<Entity*> mBullets;
};

///////////////////////////////////////////////////////////////////

void Update(Gamestate* gameState, float dt)
{
	// Update player
	gameState->mPlayer.Update(dt);
}

///////////////////////////////////////////////////////////////////

void Render(Gamestate* gameState, sf::RenderWindow* renderWin)
{
	// Render player
	gameState->mPlayer.Render(renderWin);
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
		
		Update(&gameState, frameTime.asSeconds());

		Render(&gameState, &window);

		window.display();


	}


	// Keep console window open
	getchar();
	return 0;
}

