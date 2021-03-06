#include "MiniginPCH.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#pragma comment(lib,"xinput.lib")
#include "SDL.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "Font.h"

#include "EngineTestScene.h"

const float msPerFrame = 16.66666667f; //16 for 60 fps, 33 for 30 fps

void Initialize();
void LoadGame();
void Cleanup();

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	Initialize();

	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("Resources/");

	LoadGame();
	
	{
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag{0.0f};

		auto& input = dae::InputManager::GetInstance();
		auto& sceneManager = dae::SceneManager::GetInstance();
		auto& renderer = dae::Renderer::GetInstance();

		while(doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaT = std::chrono::duration<float>(currentTime - lastTime).count() * 1000.0f;
			lastTime = currentTime;

			lag += deltaT;
			doContinue = input.ProcessInput();

			while(lag >= msPerFrame)
			{
				sceneManager.Update(float(msPerFrame / 1000.0f));
				lag -= msPerFrame;
			}
			renderer.Render();
		}
	}

	Cleanup();
    return 0;
}

SDL_Window* window;

void Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::stringstream ss; ss << "SDL_Init Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		int(GameSettings::WindowSizeX),                    
		int(GameSettings::WindowSizeY),
		SDL_WINDOW_OPENGL       
	);
	if (window == nullptr) {
		std::stringstream ss; ss << "SDL_CreateWindow Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	dae::Renderer::GetInstance().Init(window);
}

void LoadGame()
{
	dae::SceneManager::GetInstance().AddScene(new EngineTestScene());
}

void Cleanup()
{
	dae::InputManager::GetInstance().Clear();
	dae::ResourceManager::GetInstance().Clear();
	dae::SceneManager::GetInstance().CleanUp();
	dae::Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	SDL_Quit();
}

