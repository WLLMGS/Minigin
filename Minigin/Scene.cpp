#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "ColliderComponent.h"
#include <algorithm>

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

void dae::Scene::Destroy(size_t index)
{
	delete m_pGameObjects[index];
	m_pGameObjects[index] = nullptr;

	m_pGameObjects.erase(remove(m_pGameObjects.begin(), m_pGameObjects.end(), m_pGameObjects[index]), m_pGameObjects.end());
}

void dae::Scene::AddChild(GameObject* obj)
{
	m_pGameObjects.push_back(obj);
	obj->SetScene(this);
}

dae::GameObject* dae::Scene::FindGameObject(string name)
{
	for(auto obj : m_pGameObjects)
	{
		if(obj->GetName() == name)
		{
			return obj;
		}
	}
	return nullptr;
}

void dae::Scene::RootUpdate(float elapsedSec)
{
	Update(elapsedSec);
	/*for (auto gameObject : m_pGameObjects)*/

	//auto oldSize = m_pGameObjects.size();

	for (size_t t{0}; t <  m_pGameObjects.size(); ++t)
	{
		auto gameObject = m_pGameObjects[t];
		auto collider = gameObject->GetComponent<ColliderComponent>();

		if(!gameObject->IsDestroyed())
		{
			if (gameObject->IsEnabled())
			{
				gameObject->RootUpdate(elapsedSec);
			}

			//collision
			if(collider)
			{
				if(!collider->IsTrigger())
				{
					if (collider->IsDynamic()
						&& gameObject->IsEnabled())
					{
						for (size_t s{ 0 }; s < m_pGameObjects.size(); ++s)
						{
							auto other = m_pGameObjects[s];
							auto otherCollider = other->GetComponent<ColliderComponent>();

							if (otherCollider
								&& other != gameObject
								&& other->IsEnabled()
								&& !other->IsDestroyed()
								&& collider->GetCollisionIgnoreGroup() != otherCollider->GetCollisionGroup()
								&& otherCollider->GetCollisionIgnoreGroup() != collider->GetCollisionGroup()
								&& !otherCollider->IsTrigger()
								)
							{

								if (!otherCollider->IsDynamic())
								{
									if (collider->CheckCollision(otherCollider))
									{
										gameObject->OnCollisionEnter(otherCollider);
										other->OnCollisionEnter(collider);
									}
								}
								else
								{
									if (collider->CheckCollisionWithMass(otherCollider))
									{
										gameObject->OnCollisionEnter(otherCollider);
										other->OnCollisionEnter(collider);
									}
								}
							}
						}
					}
				}
				else
				{
					for (size_t s{ 0 }; s < m_pGameObjects.size(); ++s)
					{
						auto other = m_pGameObjects[s];
						auto otherCollider = other->GetComponent<ColliderComponent>();

						if (otherCollider
							&& otherCollider != collider
							&& !otherCollider->IsTrigger()
							&& otherCollider->IsDynamic())
						{
							if (collider->CheckTrigger(otherCollider))
							{
								gameObject->OnTriggerEnter(otherCollider);
								other->OnTriggerEnter(collider);
							}
						}
					}

				}
			}
			//do collision
			
		}
		else
		{
			//destroy
			Destroy(t);
		}
		
	}

	
}

void dae::Scene::RootRender()
{
	Render();
	for (const auto gameObject : m_pGameObjects)
	{
		if(gameObject->IsEnabled())	gameObject->RootRender();
	}

	Logger::GetInstance().Render();
}

void dae::Scene::RootPostUpdate()
{
	

	
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

