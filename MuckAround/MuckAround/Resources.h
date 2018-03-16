#pragma once

#include <SFML/Graphics.hpp>


struct Resources
{
	sf::Texture mPlayerTex;


	bool LoadResources()
	{
		bool loaded = true;

		loaded &= mPlayerTex.loadFromFile("assets/player.png");

		return loaded;
	}
};

