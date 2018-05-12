#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update(float elapsedSec)
{
	m_pScenes[m_ActiveSceneID]->RootUpdate(elapsedSec);
}

void dae::SceneManager::Render()
{
	m_pScenes[m_ActiveSceneID]->RootRender();
}

void dae::SceneManager::PostUpdate()
{
	
}

void dae::SceneManager::AddScene(Scene* scene)
{
	m_pScenes.push_back(scene);
}

dae::Scene* dae::SceneManager::GetScene(string name)
{
	for(Scene* scene : m_pScenes)
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
	for(Scene* scene : m_pScenes)
	{
		delete scene;
		scene = nullptr;
	}
}

void dae::SceneManager::NextScene()
{
	int newID = m_ActiveSceneID + 1;
	if(newID < m_pScenes.size())
	{
		m_ActiveSceneID = newID;
	}
	else
	{
		m_ActiveSceneID = 0;
	}
}
