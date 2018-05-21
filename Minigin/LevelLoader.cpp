#include "MiniginPCH.h"
#include "LevelLoader.h"
#include <fstream>
#include "WallPrefab.h"
#include "CoinPrefab.h"
#include "GhostPrefab.h"
#include "PacmanPrefab.h"

vector<dae::GridCell*> dae::LevelLoader::Grid;

void dae::LevelLoader::LoadLevel(string levelName, dae::Scene* scene)
{
	Grid.clear();
	string path = "Resources/Levels/";
	path += levelName;
	path += ".csv";

	ifstream file;

	file.open(path);
	//verify if file could be opened

	string line{};

	int x{0}, y{0};

	float tileSize = GameSettings::TileSize;
	

	while (file.good())
	{
		while(getline(file, line))
		{
			stringstream ss(line);
			string element;

			while(getline(ss, element, ','))
			{
				GridCell* cell = new GridCell();
				cell->x = x * tileSize;
				cell->y = y * tileSize;
				cell->xIndex = x;
				cell->yIndex = y;

				if (element == "W")
				{
					auto wall = new WallPrefab();
					wall->Translate(x * tileSize, y * tileSize, 0);

					scene->AddChild(wall);
					cell->isAccessible = false;
				}
				else if (element == "E")
				{
					//add coin
					auto coin = new CoinPrefab();
					coin->Translate(x * tileSize, y * tileSize, 0);
					scene->AddChild(coin);

					cell->isAccessible = true;
				}
				else if (element == "P")
				{
					auto player = scene->FindGameObject("Player");
					if (player) player->Transform()->SetPosition(x * tileSize, y * tileSize);

					PacmanPrefab* pacman = static_cast<PacmanPrefab*>(player);
					pacman->SetSpawnPosition(tileSize * x, tileSize * y);
					cell->isAccessible = true;

					auto coin = new CoinPrefab();
					coin->Translate(x * tileSize, y * tileSize, 0);
					scene->AddChild(coin);
				}
				else if(element == "G")
				{
					auto ghost = new GhostPrefab();
					ghost->Transform()->SetPosition(tileSize * x, tileSize * y);
					ghost->SetSpawnPosition(tileSize * x, tileSize * y);
					scene->AddChild(ghost);

					cell->isAccessible = true;

					auto coin = new CoinPrefab();
					coin->Translate(x * tileSize, y * tileSize, 0);
					scene->AddChild(coin);
				}
				Grid.push_back(cell);

				++x;
			}
			x = 0;
			++y;

		}
	}

}

void dae::LevelLoader::Clear()
{
	for(size_t t{}; t < Grid.size(); ++t)
	{
		delete Grid[t];
		Grid[t] = nullptr;
	}
}
