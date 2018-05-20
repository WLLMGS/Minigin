#include "MiniginPCH.h"
#include "PacmanPrefab.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "Scene.h"
#include "../SandBox/ScorePrefab.h"

PacmanPrefab::PacmanPrefab()
{
	auto sprite = new dae::SpriteComponent(dae::TextureName::PACMAN);
	sprite->SetAnimated(true);
	sprite->SetAnimationParameters(3, 9, 10.0f, 9.0f);

	AddComponent(sprite);
	
	auto collider = new ColliderComponent(true);
	collider->SetCollisionGroup(GameSettings::CollisionGroups::PLAYER);
	/*collider->SetOffset(2.0f, 2.0f);
	collider->SetDimensions(24.0f, 24.0f);*/

	AddComponent(collider);

	m_Speed = 100.0f;

	SetTag("Player");
	SetName("Player");
}

void PacmanPrefab::Update(float elapsedSec)
{
	auto command = dae::InputManager::GetInstance().HandleInput();

	if (command) command->Execute(this);

	m_MoveCooldown -= elapsedSec;

	if(m_MoveCooldown <= 0.0f)
	{
		m_MoveCooldown = m_Cooldown;
		Movement();
	}
}

void PacmanPrefab::OnTriggerEnter(ColliderComponent* other)
{
	if (other->gameObject->GetTag() == "Coin")
	{
		auto score = GetScene()->FindGameObject("Score");
		if(score)
		{
			ScorePrefab* s = dynamic_cast<ScorePrefab*>(score);
			s->IncreaseScore(100);
		}

		other->gameObject->Destroy();
	}
}

void PacmanPrefab::OnCollisionEnter(ColliderComponent* other)
{
	if(other->gameObject->GetTag() == "Ghost")
	{
		SetEnabled(false);
		dae::SceneManager::GetInstance().GoToScene("Game Over");
	}
}

void PacmanPrefab::Movement()
{
	switch(m_Direction)
	{
	case Right:
		Transform()->Translate(GameSettings::TileSize / 2.0f - 2.0f, 0, 0);
		break;
	case Left:
		Transform()->Translate(-GameSettings::TileSize / 2.0f - 2.0f, 0, 0);
		break;
	case Up:
		Transform()->Translate(0, -GameSettings::TileSize / 2.0f - 2.0f, 0);
		break;
	case Down:
		Transform()->Translate(0, GameSettings::TileSize / 2.0f - 2.0f, 0);
		break;
	}
}





