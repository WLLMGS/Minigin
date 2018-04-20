#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject()
{
	m_TransformComponent.m_pGameObject = this;
}

void dae::GameObject::RootUpdate(float elapsedSec)
{
	Update(elapsedSec);
	for (auto comp : m_pComponents) comp->Update(elapsedSec);
}

void dae::GameObject::RootRender()
{
	Render();
	for (auto comp : m_pComponents) comp->Render();
}

dae::GameObject::~GameObject()
{

	for(auto component : m_pComponents)
	{
		delete component;
		component = nullptr;
	}
}

void dae::GameObject::Update(float elapsedSec)
{
	for(auto component : m_pComponents)
	{
		component->Update(elapsedSec);
	}
}

void dae::GameObject::Render() const
{
	for(auto component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::Translate(float x, float y, float z)
{
	m_TransformComponent.Translate(x, y, z);
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	m_pComponents.push_back(component);
	component->m_pGameObject = this;
}

dae::TransformComponent* dae::GameObject::Transform()
{
	return &m_TransformComponent;
}



