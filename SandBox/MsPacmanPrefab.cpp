#include "stdafx.h"
#include "MsPacmanPrefab.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "InputManager.h"
#include "ScorePrefab.h"
#include "Scene.h"
#include "GhostPrefab.h"

MsPacmanPrefab::MsPacmanPrefab()
{
	auto sprite = new dae::SpriteComponent(dae::TextureName::MSPACMAN);
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
	m_Direction = Down;
}


MsPacmanPrefab::~MsPacmanPrefab()
{
}

void MsPacmanPrefab::Update(float elapsedSec)
{
	auto command = dae::InputManager::GetInstance().HandleInput(2);

	if (command) command->Execute(this);

	m_MoveCooldown -= elapsedSec;

	if (m_MoveCooldown <= 0.0f)
	{
		m_MoveCooldown = m_Cooldown;
		Movement();
	}
}

void MsPacmanPrefab::OnTriggerEnter(ColliderComponent* other)
{
	if (other->gameObject->GetTag() == "Coin")
	{
		auto score = GetScene()->FindGameObject("Score");
		if (score)
		{
			ScorePrefab* s = dynamic_cast<ScorePrefab*>(score);
			s->IncreaseScore(100);
		}

		other->gameObject->Destroy();
	}
	if (other->gameObject->GetTag() == "Pill")
	{
		vector<GameObject*> ghosts = GetScene()->GetObjectsWithTag("Ghost");

		for (auto obj : ghosts)
		{
			GhostPrefab* g = static_cast<GhostPrefab*>(obj);
			g->SetState(GhostPrefab::Running);
			other->gameObject->Destroy();
		}
	}
}

void MsPacmanPrefab::OnCollisionEnter(ColliderComponent* other)
{
	if (other->gameObject->GetTag() == "Ghost")
	{
		GhostPrefab* ghost = static_cast<GhostPrefab*>(other->gameObject);
		GhostPrefab::State state = ghost->GetState();

		if (state == GhostPrefab::Running)
		{
			//kill ghost
			ghost->SetEnabled(false);
		}
		else
		{
			if (m_Lives >= 0)
			{
				m_Lives -= 1;
				Transform()->SetPosition(GetSpawnPosition().x, GetSpawnPosition().y);
			}
			else
			{
				SetEnabled(false);
				dae::SceneManager::GetInstance().GoToScene("Game Over");
			}

		}

	}
}

void MsPacmanPrefab::Movement()
{
	switch (m_Direction)
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
