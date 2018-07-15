#pragma once

#include <SFML/Graphics.hpp>


struct Resources
{
	sf::Texture mPlayerTex;

	////////////////////////////////////////////////////////////////////
	Resources() {}
	~Resources() {}

	bool LoadResources();
};

