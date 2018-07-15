#include "Resources.h"

bool Resources::LoadResources()
{
	bool loaded = true;

	loaded &= mPlayerTex.loadFromFile("assets/player.png");

	return loaded;
}

