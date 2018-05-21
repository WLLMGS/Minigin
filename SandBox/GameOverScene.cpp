#include "stdafx.h"
#include "GameOverScene.h"
#include "PacmanDemoScene.h"
#include "InputManager.h"


GameOverScene::GameOverScene() :
Scene("Game Over")
{
	InitButtons();
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update(float elapsedSec)
{
	m_CoolDown -= elapsedSec;

	auto& input = dae::InputManager::GetInstance();

	if (input.IsKeyPressed(SDLK_SPACE) || input.IsPressed(dae::ControllerButton::ButtonA))
	{
		for (auto button : m_pButtons)
		{
			if (button->IsSelected())
			{
				button->Activate();
				break;
			}
		}
	}

	if (input.IsPressed(dae::ControllerButton::DpadDown) || input.IsKeyPressed(SDLK_s))
	{
		if (m_CoolDown < 0.0f)
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

	if (input.IsPressed(dae::ControllerButton::DpadUp) || input.IsKeyPressed(SDLK_z) || input.IsKeyPressed(SDLK_w))
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

void GameOverScene::InitButtons()
{
	//play single player
	auto button = new ButtonPrefab(dae::MEDIUM, { 0,0,255,255 }, "Restart");
	button->Transform()->Translate(GameSettings::WindowSizeX / 2.0f - GameSettings::TileSize * 3.0f, GameSettings::TileSize * 3.0f, 0);

	auto restart = []() ->void
	{
		dae::SceneManager::GetInstance().RemoveScene("Pacman Demo Scene");
		dae::SceneManager::GetInstance().AddScene(new PacmanDemoScene());
		dae::SceneManager::GetInstance().GoToScene("Pacman Demo Scene");
	};

	button->SetAction(restart);
	AddChild(button);

	m_pButtons.push_back(button);


	//quit
	button = new ButtonPrefab(dae::MEDIUM, { 0,0,255,255 }, "Quit");
	button->Transform()->Translate(GameSettings::WindowSizeX / 2.0f - GameSettings::TileSize * 3.0f, GameSettings::TileSize * 4.0f, 0);

	auto quit = []() ->void
	{
		dae::InputManager::GetInstance().Quit();
	};

	button->SetAction(quit);

	AddChild(button);
	m_pButtons.push_back(button);


	m_pButtons[0]->SetSelected(true);
}
