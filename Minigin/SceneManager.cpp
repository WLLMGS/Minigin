#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update(float elapsedSec)
{
	for(auto scene : mScenes)
	{
		scene->RootUpdate(elapsedSec);
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : mScenes)
	{
		scene->RootRender();
	}
}

void dae::SceneManager::AddScene(Scene* scene)
{
	mScenes.push_back(scene);
}

dae::Scene* dae::SceneManager::GetScene(string name)
{
	for(Scene* scene : mScenes)
	{
		if(scene->GetName() == name)
		{
			return scene;
		}
	}

	return nullptr;
}

void dae::SceneManager::CleanUp()
{
	for(Scene* scene : mScenes)
	{
		delete scene;
		scene = nullptr;
	}
}
