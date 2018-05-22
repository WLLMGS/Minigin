#include "stdafx.h"
#include "MainMenu.h"
#include "InputManager.h"
#include <SDL.h>
#include "TextComponent.h"
#include "PacmanDemoScene.h"


MainMenu::MainMenu() :
Scene("Main Menu")
{
	auto titleObj = new dae::GameObject();
	auto title = new TextComponent(dae::BIG, { 255,0,0,255 }, "Pac-Man");

	titleObj->AddComponent(title);
	titleObj->Transform()->Translate(GameSettings::WindowSizeX / 2.0f - GameSettings::TileSize * 3.0f, GameSettings::TileSize, 0);

	AddChild(titleObj);

	InitButtons();
}


MainMenu::~MainMenu()
{
}

void MainMenu::Update(float elapsedSec)
{
	m_CoolDown -= elapsedSec;

	auto& input = dae::InputManager::GetInstance();

	if(input.IsKeyPressed(SDLK_RETURN) || input.IsPressed(dae::ControllerButton::ButtonA))
	{
		for(auto button : m_pButtons)
		{
			if (button->IsSelected())
			{
				button->Activate();
				break;
			}
		}
	}

	if(input.IsPressed(dae::ControllerButton::DpadDown) || input.IsKeyPressed(SDLK_s) || input.IsKeyPressed(SDLK_DOWN))
	{
		if(m_CoolDown < 0.0f)
		{
			m_CoolDown = 0.1f;
			for (size_t t{}; t < m_pButtons.size(); ++t)
			{
				if (m_pButtons[t]->IsSelected())
				{
					if (t < m_pButtons.size() - 1) m_pButtons[t + 1]->SetSelected(true);
					
					
					else m_pButtons[0]->SetSelected(true);
					
					m_pButtons[t]->SetSelected(false);
					break;
				}
			}
		}
		
	}

	if(input.IsPressed(dae::ControllerButton::DpadUp) || input.IsKeyPressed(SDLK_z) || input.IsKeyPressed(SDLK_w) || input.IsKeyPressed(SDLK_UP))
	{
		if (m_CoolDown < 0.0f)
		{
			m_CoolDown = 0.1f;
			for (size_t t{}; t < m_pButtons.size(); ++t)
			{
				if (m_pButtons[t]->IsSelected())
				{
					if (t >= 1) m_pButtons[t - 1]->SetSelected(true);
					else m_pButtons[m_pButtons.size() - 1]->SetSelected(true);

					m_pButtons[t]->SetSelected(false);
					break;
				}
			}
		}
	}

	

}

void MainMenu::InitButtons()
{
	//play single player
	auto button = new ButtonPrefab(dae::MEDIUM, { 0,0,255,255 }, "Singleplayer");
	button->Transform()->Translate(GameSettings::WindowSizeX / 2.0f - GameSettings::TileSize * 3.0f, GameSettings::TileSize * 3.0f, 0);

	auto play = []() ->void
	{
		dae::SceneManager::GetInstance().AddScene(new PacmanDemoScene());
		dae::SceneManager::GetInstance().GoToScene("Pacman Demo Scene");
	};

	button->SetAction(play);
	AddChild(button);

	m_pButtons.push_back(button);

	//play multiplayer
	button = new ButtonPrefab(dae::MEDIUM, { 0,0,255,255 }, "Multiplayer (Ghost)");
	button->Transform()->Translate(GameSettings::WindowSizeX / 2.0f - GameSettings::TileSize * 3.0f, GameSettings::TileSize * 4.0f, 0);

	auto multiplayer = []() ->void
	{
		dae::SceneManager::GetInstance().AddScene(new PacmanDemoScene(PacmanDemoScene::MultiplayerGhost));
		dae::SceneManager::GetInstance().GoToScene("Pacman Demo Scene");
	};
	button->SetAction(multiplayer);
	AddChild(button);

	m_pButtons.push_back(button);


	button = new ButtonPrefab(dae::MEDIUM, { 0,0,255,255 }, "Multiplayer (Ms. Pacman)");
	button->Transform()->Translate(GameSettings::WindowSizeX / 2.0f - GameSettings::TileSize * 3.0f, GameSettings::TileSize * 5.0f, 0);

	auto multiplayer2 = []() -> void
	{
		dae::SceneManager::GetInstance().AddScene(new PacmanDemoScene(PacmanDemoScene::MultiplayerMsPacman));
		dae::SceneManager::GetInstance().GoToScene("Pacman Demo Scene");
	};

	button->SetAction(multiplayer2);
	AddChild(button);

	m_pButtons.push_back(button);

	//quit
	button = new ButtonPrefab(dae::MEDIUM, { 0,0,255,255 }, "Quit");
	button->Transform()->Translate(GameSettings::WindowSizeX / 2.0f - GameSettings::TileSize * 3.0f, GameSettings::TileSize * 6.0f, 0);

	auto quit = []() ->void
	{
		dae::InputManager::GetInstance().Quit();
	};

	button->SetAction(quit);

	AddChild(button);
	m_pButtons.push_back(button);


	//activate first
	m_pButtons[0]->SetSelected(true);


	

	

}
