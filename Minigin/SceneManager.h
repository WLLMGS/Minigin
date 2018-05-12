#pragma once
#include "Singleton.h"
#include <string>
#include <vector>

using namespace std;

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void Update(float elapsedSec);
		void Render();
		void PostUpdate();
		void AddScene(Scene* scene);
		Scene* GetScene(string name);
		void CleanUp();
		void NextScene();
	private:
		std::vector<Scene*> m_pScenes;
		int m_ActiveSceneID = 0;
	};

}
