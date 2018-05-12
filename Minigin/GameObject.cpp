#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject()
{
	m_TransformComponent.gameObject = this;
}

void dae::GameObject::RootUpdate(float elapsedSec)
{
	Update(elapsedSec);
	for (auto comp : m_pComponents) comp->Update(elapsedSec);
	for (auto child : m_pChildren) child->RootUpdate(elapsedSec);
}

void dae::GameObject::RootRender()
{
	Render();
	for (auto comp : m_pComponents) comp->Render();
	for (auto child : m_pChildren) child->RootRender();
}

dae::GameObject::~GameObject()
{

	for(auto component : m_pComponents)
	{
		delete component;
		component = nullptr;
	}

	for(auto child : m_pChildren)
	{
		delete child;
		child = nullptr;
	}
}

void dae::GameObject::OnCollisionEnter(ColliderComponent* other)
{
	(other);
}

void dae::GameObject::OnTriggerEnter(ColliderComponent* other)
{
	(other);
}

void dae::GameObject::SetTag(string tag)
{
	m_Tag = tag;
}

string dae::GameObject::GetTag()
{
	return m_Tag;
}

void dae::GameObject::SetName(string name)
{
	m_Name = name;
}

string dae::GameObject::GetName()
{
	return m_Name;
}

void dae::GameObject::SetScene(Scene* scene)
{
	m_pScene = scene;
}

dae::Scene* dae::GameObject::GetScene()
{
	return m_pScene;
}

void dae::GameObject::SetEnabled(const bool enable)
{
	m_IsEnabled = enable;

	for (auto child : m_pChildren) child->SetEnabled(child);
}

bool dae::GameObject::IsEnabled()
{
	return m_IsEnabled;
}

void dae::GameObject::Destroy()
{
	m_IsDestroyed = true;
}

bool dae::GameObject::IsDestroyed()
{
	return m_IsDestroyed;
}

void dae::GameObject::SetMass(float mass)
{
	if (m_Mass < 1.0f) m_Mass = 1.0f;
	else m_Mass = mass;
}

float dae::GameObject::GetMass()
{
	return m_Mass;
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
	component->SetGameObject(this);
}

void dae::GameObject::AddChild(GameObject* child)
{
	child->SetScene(GetScene());
	m_pChildren.push_back(child);
}

dae::TransformComponent* dae::GameObject::Transform()
{
	return &m_TransformComponent;
}

vector<dae::GameObject*> dae::GameObject::GetChildren()
{
	return m_pChildren;
}



