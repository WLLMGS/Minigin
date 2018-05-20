#include "stdafx.h"
#include "Game.h"
#include "SceneManager.h"
#include "EngineTestScene.h"
#include "PacmanDemoScene.h"
#include "MainMenu.h"
#include "GameOverScene.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::LoadGameData()
{
	dae::SceneManager::GetInstance().AddScene(new MainMenu());
	dae::SceneManager::GetInstance().AddScene(new GameOverScene());
}
