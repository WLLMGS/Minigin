#pragma once
#include "SceneManager.h"
#include "GameObject.h"

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
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		void AddChild(GameObject* obj);

		private: 
		

		std::string mName{};
		std::vector < GameObject*> mObjects{};

		static unsigned int idCounter; 

	private:
		friend class SceneManager;

		void RootUpdate(float elapsedSec);
		void RootRender();
	};

}

