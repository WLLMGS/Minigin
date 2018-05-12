#include "MiniginPCH.h"
#include "PathFinder.h"
#include <deque>
#include <map>
#include <algorithm>

vector<dae::GridCell*> PathFinder::FindPath(dae::GridCell* target, dae::GridCell* source)
{
	deque<dae::GridCell*> queue;
	bool found = false;

	map<dae::GridCell*, int> values;
	map<dae::GridCell*, dae::GridCell*> parents;

	queue.push_back(source);
	int value{};

	dae::GridCell* current = source;

	while(!queue.empty() && !found)
	{
		auto isCheapest = [&values](dae::GridCell* c1, dae::GridCell* c2)
		{
			return values[c1] < values[c2];
		};
		
		current = *min_element(queue.begin(), queue.end(), isCheapest);
		queue.erase(remove(queue.begin(), queue.end(), current), queue.end());

		value = values[current];

		//check neighbors
		for(auto n : GetNeighbors(current->xIndex, current->yIndex))
		{
			if (n == target) found = true;

			if(values.find(n) == values.end())
			{
				values[n] = value + 1;
				queue.push_back(n);
				parents[n] = current;
			}
		}

	}

	vector<dae::GridCell*> path;

	if(found)
	{	
		dae::GridCell* p = current;
		bool loop = true;

		while(loop)
		{	
			path.push_back(p);
			
			if (parents[p]) p = parents[p];
			else loop = false;
		}

		reverse(path.begin(), path.end());
		Logger::GetInstance().Log("found");
	}

	return path;
}

vector<dae::GridCell*> PathFinder::GetNeighbors(int x, int y)
{
	auto grid = dae::LevelLoader::Grid;

	vector<dae::GridCell*> result;

	int width = int(GameSettings::WindowSizeX / GameSettings::TileSize);
	int height = int(GameSettings::WindowSizeY / GameSettings::TileSize);

	//int index = y * width + x;

	int left = y * width + (x - 1);
	int right = y * width + (x + 1);

	int up = (y + 1) * width + x;
	int down = (y - 1) * width + x;

	if (y > 0)
	{
		if(grid[down]->isAccessible) result.push_back(grid[down]);
	}
	if (y < height)
	{
		if(grid[up]->isAccessible) result.push_back(grid[up]);
	}
	if (x > 0)
	{
		if(grid[left]->isAccessible) result.push_back(grid[left]);
	}
	if (x < width)
	{
		if(grid[right]->isAccessible) result.push_back(grid[right]);
	}

	return result;
}


