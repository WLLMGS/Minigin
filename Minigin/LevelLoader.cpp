#include "MiniginPCH.h"
#include "LevelLoader.h"
#include <fstream>
#include "WallPrefab.h"

void dae::LevelLoader::LoadLevel(string levelName, dae::Scene* scene)
{
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
				if(element == "W")
				{
					auto wall = new WallPrefab();
					wall->Translate(x * tileSize, y * tileSize, 1);
					
					scene->AddChild(wall);
				}
				++x;
			}
			x = 0;
			++y;

		}
	}

}
