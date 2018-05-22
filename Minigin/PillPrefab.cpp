#include "MiniginPCH.h"
#include "PillPrefab.h"
#include "../SandBox/GameOverScene.h"
#include "SpriteComponent.h"


PillPrefab::PillPrefab()
{
	auto sprite = new dae::SpriteComponent(dae::TextureName::PILL);
	AddComponent(sprite);

	auto collider = new ColliderComponent(false);
	collider->SetTrigger(true);


	AddComponent(collider);

	SetTag("Pill");
}


PillPrefab::~PillPrefab()
{
}
