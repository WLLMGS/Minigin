#pragma once
#include <vector>

#include "TransformComponent.h"
#include "ColliderComponent.h"

using namespace std;

namespace dae
{
	class Scene;

	class GameObject
	{
	public:
		GameObject();
		void RootUpdate(float elapsedSec);
		void RootRender();
		void Translate(float x, float y, float z);
		void AddComponent(BaseComponent* component);
		void AddChild(GameObject* child);
		TransformComponent* Transform();
		vector<GameObject*> GetChildren();

		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void OnCollisionEnter(ColliderComponent* other);
		virtual void OnTriggerEnter(ColliderComponent* other);
		void SetTag(string tag);
		string GetTag();

		void SetName(string name);
		string GetName();

		void SetScene(Scene* scene);
		Scene* GetScene();
		void SetEnabled(const bool enable);
		bool IsEnabled();
		void Destroy();
		bool IsDestroyed();
		void SetMass(float mass);
		float GetMass();

	public:
		template<class T> T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto *component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}
	protected:
		virtual void Update(float elapsedSec);
		virtual void Render() const;

		Scene* m_pScene;
	private:
		
		string m_Tag = "Default";
		//Texture2D* m_pTexture2D;
		TransformComponent m_TransformComponent;
		vector<BaseComponent*> m_pComponents;
		bool m_IsEnabled = true;
		bool m_IsDestroyed = false;
		float m_Mass = 1.0f;

		vector<GameObject*> m_pChildren;

		string m_Name = "";
	};
}
