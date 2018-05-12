#pragma once
//#define DEBUG

namespace GameSettings
{
	const float WindowSizeX = 512.0f;
	const float WindowSizeY = 512.0f;
	const float TileSize = 32.0f;
	const int FontSize = 24;

	enum CollisionGroups
	{
		PLAYER = 1,
		ENEMY = 2,
		WALL = 3
	};
}