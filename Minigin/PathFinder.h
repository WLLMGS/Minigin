#pragma once
#include "LevelLoader.h"

class PathFinder
{
public:
	static vector<dae::GridCell*> FindPath(dae::GridCell* target,dae::GridCell* source);

private:
	static vector<dae::GridCell*> GetNeighbors(int x, int y);
};

