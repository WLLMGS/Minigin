#include "MiniginPCH.h"
#include "MiniginGame.h"
#include "Renderer.h"
#include "GameSettings.h"
#include "ResourceManager.h"
#include <chrono>
#include "SceneManager.h"
#include "InputManager.h"


MiniginGame::MiniginGame()
{
}


MiniginGame::~MiniginGame()
{
}

void MiniginGame::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::stringstream ss; ss << "SDL_Init Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	m_pWindow = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		int(GameSettings::WindowSizeX),
		int(GameSettings::WindowSizeY),
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr) {
		std::stringstream ss; ss << "SDL_CreateWindow Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	dae::Renderer::GetInstance().Init(m_pWindow);

	dae::ResourceManager::GetInstance().Init("Resources/");
}

void MiniginGame::Run()
{

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag{ 0.0f };

	auto& input = dae::InputManager::GetInstance();
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& renderer = dae::Renderer::GetInstance();

	while (doContinue)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		float deltaT = chrono::duration<float>(currentTime - lastTime).count() * 1000.0f;
		lastTime = currentTime;

		lag += deltaT;
		doContinue = input.ProcessInput();

		while (lag >= m_MsPerFrame)
		{
			sceneManager.Update(float(m_MsPerFrame / 1000.0f));
			Update(float(m_MsPerFrame / 1000.0f));
			lag -= m_MsPerFrame;
		}
		renderer.Render();
		sceneManager.PostUpdate();
	}
}

void MiniginGame::Cleanup()
{
	dae::InputManager::GetInstance().Clear();
	dae::ResourceManager::GetInstance().Clear();
	dae::SceneManager::GetInstance().CleanUp();
	dae::Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void MiniginGame::LoadGameData()
{
	//load scenes here
}

void MiniginGame::Update(float elapsedSec)
{
	(elapsedSec);
}

void MiniginGame::Render()
{
}
