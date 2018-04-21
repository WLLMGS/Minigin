#include "MiniginPCH.h"
#include "WallPrefab.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "ColliderComponent.h"


WallPrefab::WallPrefab()
{
	auto sprite = new dae::SpriteComponent(dae::WALL_1);
	AddComponent(sprite);
	AddComponent(new ColliderComponent(false));
}


WallPrefab::~WallPrefab()
{
}
