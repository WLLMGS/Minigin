#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name) { }


dae::Scene::~Scene()
{
	for(GameObject* object: m_pGameObjects)
	{
		delete object;
		object = nullptr;
	}
}

void dae::Scene::AddChild(GameObject* obj)
{
	m_pGameObjects.push_back(obj);
}

void dae::Scene::RootUpdate(float elapsedSec)
{
	Update(elapsedSec);
	for (auto gameObject : m_pGameObjects)
	{
		gameObject->RootUpdate(elapsedSec);
	}
}

void dae::Scene::RootRender()
{
	Render();
	for (const auto gameObject : m_pGameObjects)
	{
		gameObject->RootRender();
	}

	Logger::GetInstance().Render();
}

void dae::Scene::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::Scene::Render() const
{
	
}

string dae::Scene::GetName() const
{
	return mName;
}

