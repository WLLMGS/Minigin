#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>

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

void dae::SceneManager::RemoveScene(string name)
{
	
	for(size_t t{}; t < m_pScenes.size(); ++t)
	{
		auto scene = m_pScenes[t];

		if(scene->GetName() == name)
		{
			delete scene;
			scene = nullptr;
			m_pScenes.erase(remove(m_pScenes.begin(), m_pScenes.end(), m_pScenes[t]), m_pScenes.end());
			break;
		}
	}

	
}

void dae::SceneManager::GoToScene(string name)
{
	for(size_t t{}; t < m_pScenes.size(); ++t)
	{
		if(m_pScenes[t]->GetName() == name)
		{
			m_ActiveSceneID = int(t);
			break;
		}
	}
}
