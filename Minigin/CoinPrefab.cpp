#include "MiniginPCH.h"
#include "CoinPrefab.h"
#include "SpriteComponent.h"
#include "TextComponent.h"


CoinPrefab::CoinPrefab()
{
	auto sprite = new dae::SpriteComponent(dae::TextureName::COIN);
	AddComponent(sprite);

	auto collider = new ColliderComponent(false);
	collider->SetTrigger(true);


	AddComponent(collider);

	SetTag("Coin");
}


CoinPrefab::~CoinPrefab()
{
}



