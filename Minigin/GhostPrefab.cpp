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

	m_MoveCooldown -= elapsedSec;

	if(m_MoveCooldown <= 0.0f)
	{
		m_MoveCooldown = m_Cooldown;
		CalculateMovement(elapsedSec);
	}
}

void GhostPrefab::CalculateMovement(float elapsedSec)
{

	UNREFERENCED_PARAMETER(elapsedSec);

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

	if (path.size() > 1)
		{
			auto cell = path[1];
			auto current = m_pGrid[index];


			float horz = 0.0f;
			float vert = 0.0f;

			if(cell->xIndex == current->xIndex && cell->yIndex > current->yIndex)
			{
				//up
				vert = m_Speed;
			}
			else if (cell->xIndex == current->xIndex && cell->yIndex < current->yIndex)
			{
				//down
				vert = -m_Speed;
			}
			if (cell->yIndex == current->yIndex && cell->xIndex > current->xIndex)
			{
				//right
				horz = m_Speed;
			}
			else if (cell->yIndex == current->yIndex && cell->xIndex < current->xIndex)
			{
				//left
				horz = -m_Speed;
			}



			//cout << "Target: " << cell->x << " " << cell->y << endl;
			//cout << "Source: " << current->x << " " << current->y << endl;

			cout << horz << " " << vert << endl;

			//Transform()->Translate(horz * elapsedSec, vert * elapsedSec, 0);
			Transform()->SetPosition(cell->x, cell->y);


		}
	else
	{
		cout << "not good\n";
	}
	
	
}


