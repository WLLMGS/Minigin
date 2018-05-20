#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include "Logger.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		
	public:
		Scene(const string& name);
		virtual void Update(float elapsedSec);
		void Render() const;
		string GetName() const;
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		void AddChild(GameObject* obj);
		GameObject* FindGameObject(string name);
		vector<GameObject*> GetObjectsWithTag(string tag);
	protected:
		std::vector < GameObject*> m_pGameObjects{};
	private: 
		std::string mName{};
		static unsigned int idCounter; 
		vector<GameObject*> m_pClear;
		void Destroy(size_t index);
	private:
		friend class SceneManager;
		friend class LevelLoader;

		void RootUpdate(float elapsedSec);
		void RootRender();
		void RootPostUpdate();
	};

}

