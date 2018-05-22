#include "stdafx.h"
#include "PacmanDemoScene.h"
#include "FpsCounterPrefab.h"
#include "PacmanPrefab.h"
#include "LevelLoader.h"
#include "InputManager.h"
#include <SDL.h>
#include <iostream>
#include "PathFinder.h"
#include "ScorePrefab.h"
#include "GhostPrefab.h"
#include "MsPacmanPrefab.h"


PacmanDemoScene::PacmanDemoScene(GameMode mode) :
Scene("Pacman Demo Scene"),
m_Mode(mode)
{	
	Init();
}


PacmanDemoScene::~PacmanDemoScene()
{
	dae::LevelLoader::Clear();
}

void PacmanDemoScene::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);

}

void PacmanDemoScene::Render()
{
}

void PacmanDemoScene::Reset()
{
	for(auto obj : m_pGameObjects)
	{
		delete obj;
		obj = nullptr;
	}

	m_pGameObjects.clear();

	Init();
}

void PacmanDemoScene::Init()
{
	m_pPacman = new PacmanPrefab();
	m_pPacman->Translate(10, 100, 1);
	AddChild(m_pPacman);

	dae::LevelLoader::LoadLevel("level01", this);

	auto score = new ScorePrefab();
	score->Transform()->SetPosition(GameSettings::WindowSizeX / 2.0f - GameSettings::TileSize * 2.0f, 0);
	AddChild(score);

	if(m_Mode == MultiplayerGhost)
	{
		auto ghosts = this->GetObjectsWithTag("Ghost");

		GhostPrefab* ghost1 = static_cast<GhostPrefab*>(ghosts[0]);

		ghost1->SetControlled();
	}
	else if(m_Mode == MultiplayerMsPacman)
	{
		//spawn ms pacman here
		auto msPacman = new MsPacmanPrefab();
		msPacman->Transform()->SetPosition(m_pPacman->Transform()->GetPosition().x, m_pPacman->Transform()->GetPosition().y);

		AddChild(msPacman);
	}
	
}
