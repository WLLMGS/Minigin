#pragma once
#include "Scene.h"
namespace dae
{
	struct GridCell
	{
		GridCell() : 
		x(0.0f),
		y(0.0f),
		isAccessible(false)
		{}
		float x, y;
		int xIndex, yIndex;
		bool isAccessible;
	};

	class LevelLoader
	{
	public:
		static void LoadLevel(string fileName, Scene* scene);
		static vector<GridCell*> Grid;
		static void Clear();
	private:
	};
}


