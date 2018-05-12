#include "stdafx.h"
#include "PacmanDemoScene.h"
#include "FpsCounterPrefab.h"
#include "PacmanPrefab.h"
#include "LevelLoader.h"
#include "InputManager.h"
#include <SDL.h>
#include <iostream>
#include "PathFinder.h"


PacmanDemoScene::PacmanDemoScene() :
Scene("Pacman demo scene")
{
	
	m_pPacman = new PacmanPrefab();
	m_pPacman->Translate(10, 100, 1);
	AddChild(m_pPacman);



	dae::LevelLoader::LoadLevel("level01", this);
	
	auto fpsCounter = new FpsCounterPrefab();
	//fpsCounter->Translate(10, 10, 1);
	AddChild(fpsCounter);

}


PacmanDemoScene::~PacmanDemoScene()
{
	dae::LevelLoader::Clear();
}

void PacmanDemoScene::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);

	/*auto grid = dae::LevelLoader::Grid;

	int width = int(GameSettings::WindowSizeX / GameSettings::TileSize);
	
	auto c1 = grid[width * 4 + 2];
	auto c2 = grid[width * 1 + 6];

	auto path = PathFinder::FindPath(c2, c1);*/
}

void PacmanDemoScene::Render()
{
}
