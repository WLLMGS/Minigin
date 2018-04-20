#include "MiniginPCH.h"
#include "PacmanPrefab.h"
#include "SpriteComponent.h"
#include "TextComponent.h"


PacmanPrefab::PacmanPrefab()
{
	auto sprite = new dae::SpriteComponent(dae::TextureName::PACMAN);
	sprite->SetAnimated(true);
	sprite->SetAnimationParameters(3, 9, 10.0f, 9.0f);

	AddComponent(sprite);
}



