#include "MiniginPCH.h"
#include "WallPrefab.h"
#include "SpriteComponent.h"
#include "TextComponent.h"


WallPrefab::WallPrefab()
{
	auto sprite = new dae::SpriteComponent(dae::WALL_1);
	AddComponent(sprite);
}


WallPrefab::~WallPrefab()
{
}
