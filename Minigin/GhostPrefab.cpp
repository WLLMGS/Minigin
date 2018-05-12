#include "MiniginPCH.h"
#include "GhostPrefab.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "Scene.h"
#include "PathFinder.h"

dae::GameObject* GhostPrefab::m_pPlayer = nullptr;
vector<dae::GridCell*> GhostPrefab::m_pGrid;

GhostPrefab::GhostPrefab()
{
	auto sprite = new dae::SpriteComponent(dae::TextureName::GHOST);
	AddComponent(sprite);

	/*auto collider = new ColliderComponent(true);
	AddComponent(collider);*/

	SetTag("Ghost");
}


GhostPrefab::~GhostPrefab()
{
}

void GhostPrefab::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);

	if(!m_pPlayer)
	{
		m_pPlayer = GetScene()->FindGameObject("Player");
	}
	if (m_pGrid.empty()) m_pGrid = dae::LevelLoader::Grid;

	CalculateMovement(elapsedSec);
}

void GhostPrefab::CalculateMovement(float elapsedSec)
{
	float xP = m_pPlayer->Transform()->GetPosition().x;
	float yP = m_pPlayer->Transform()->GetPosition().y;

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

	
}


