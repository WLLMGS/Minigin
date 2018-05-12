#include "stdafx.h"
#include "Game.h"
#include "SceneManager.h"
#include "EngineTestScene.h"
#include "PacmanDemoScene.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::LoadGameData()
{
	dae::SceneManager::GetInstance().AddScene(new PacmanDemoScene());
}
