#pragma once
#include "Singleton.h"
#include <string>

using namespace std;

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void Update(float elapsedSec);
		void Render();
		void AddScene(Scene* scene);
		Scene* GetScene(string name);
		void CleanUp();
	private:
		std::vector<Scene*> mScenes;
	};

}
