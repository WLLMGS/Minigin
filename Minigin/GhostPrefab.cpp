#include "MiniginPCH.h"
#include "GhostPrefab.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "Scene.h"
#include "PathFinder.h"
#include "InputManager.h"

GhostPrefab::GhostPrefab() :
m_State(Chasing)
{
	auto sprite = new dae::SpriteComponent(dae::TextureName::GHOST);
	AddComponent(sprite);

	auto collider = new ColliderComponent(true);
	
	AddComponent(collider);

	SetTag("Ghost");
}


GhostPrefab::~GhostPrefab()
{
}

void GhostPrefab::Update(float elapsedSec)
{	
	//lock rotation
	Transform()->SetRotation(0);

	//check if there needs to be a state switch
	if(m_State != Controlled) HandleStateSwitching(elapsedSec);

	//handle behaviour depending to state
	switch (m_State)
	{
	case Chasing:
		HandleChasing(elapsedSec);
		break;
	case Running:
		HandleRunning(elapsedSec);
		break;
	case Controlled:
		HandleControlled(elapsedSec);
		break;
	}
}

void GhostPrefab::SetControlled(bool controlled)
{
	m_IsControlled = controlled;
}

bool GhostPrefab::IsControlled() const
{
	return m_IsControlled;
}

GhostPrefab::State GhostPrefab::GetState() const
{
	return m_State;
}

void GhostPrefab::SetState(State state)
{
	m_State = state;

	if(m_State == Chasing)
	{
		m_StateTimer = m_ChaseTime;
	}
	else m_StateTimer = m_RunTime;
}

void GhostPrefab::CalculateMovement(float elapsedSec, float targetX, float targetY)
{

	UNREFERENCED_PARAMETER(elapsedSec);

	//float xP = m_pPlayer->Transform()->GetPosition().x;
	//float yP = m_pPlayer->Transform()->GetPosition().y;

	float xP = targetX;
	float yP = targetY;

	int gridXP = int(xP / GameSettings::TileSize);
	int gridYP = int(yP / GameSettings::TileSize);

	int gridWidth = int(GameSettings::WindowSizeX / GameSettings::TileSize);

	int indexP = gridWidth * gridYP + gridXP;

	float x = Transform()->GetPosition().x;
	float y = Transform()->GetPosition().y;

	int gridX = int(x / GameSettings::TileSize);
	int gridY = int(y / GameSettings::TileSize);

	int index = gridWidth * gridY + gridX;

	auto path = PathFinder::FindPath(m_pGrid[indexP], m_pGrid[index]);

	if (path.size() > 1)
	{
		auto cell = path[1];
		
		Transform()->SetPosition(cell->x, cell->y);

		if(cell->x > x)
		{
			m_Direction = Right;
			GetComponent<dae::SpriteComponent>()->SetMirrored(false);
		}
		else if(cell->x < x)
		{
			m_Direction = Left;
			GetComponent<dae::SpriteComponent>()->SetMirrored(true);
		}

		if (cell->y > y)
		{
			m_Direction = Down;
		}
		else if (cell->y < y)
		{
			m_Direction = Up;
		}
	}
	
	
}

void GhostPrefab::Movement()
{
	switch (m_Direction)
	{
	case Right:
		Transform()->Translate(GameSettings::TileSize, 0, 0);
		GetComponent<dae::SpriteComponent>()->SetMirrored(false);
		break;
	case Left:
		Transform()->Translate(-GameSettings::TileSize, 0, 0);
		GetComponent<dae::SpriteComponent>()->SetMirrored(true);
		break;
	case Up:
		Transform()->Translate(0, -GameSettings::TileSize, 0);
		break;
	case Down:
		Transform()->Translate(0, GameSettings::TileSize, 0);
		break;
	}
}

void GhostPrefab::HandleChasing(float elapsedSec)
{
	if (!m_pPlayer)
	{
		m_pPlayer = GetScene()->FindGameObject("Player");
	}
	if (m_pGrid.empty()) m_pGrid = dae::LevelLoader::Grid;

	m_MoveCooldown -= elapsedSec;

	if (m_MoveCooldown <= 0.0f)
	{
		m_MoveCooldown = m_Cooldown;
		CalculateMovement(elapsedSec, m_pPlayer->Transform()->GetPosition().x, m_pPlayer->Transform()->GetPosition().y);
	}
}

void GhostPrefab::HandleRunning(float elapsedSec)
{
	m_MoveCooldown -= elapsedSec;

	if (m_MoveCooldown <= 0.0f)
	{
		m_MoveCooldown = m_Cooldown;
		CalculateMovement(elapsedSec, GetSpawnPosition().x, GetSpawnPosition().y);
	}
}

void GhostPrefab::HandleControlled(float elapsedSec)
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

void GhostPrefab::HandleStateSwitching(float elapsedSec)
{
	m_StateTimer -= elapsedSec;

	if(m_StateTimer <= 0.0f)
	{
		if(m_State == Chasing)
		{
			m_State = Running;
			m_StateTimer = m_RunTime;
		}
		else
		{
			m_State = Chasing;
			m_StateTimer = m_ChaseTime;
		}
	}
}


