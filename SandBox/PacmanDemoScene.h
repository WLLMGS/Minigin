#pragma once
#include "Scene.h"

class PacmanDemoScene : public dae::Scene
{
public:
	PacmanDemoScene();
	~PacmanDemoScene();
	virtual void Update(float elapsedSec) override;
	virtual void Render();
private:
	dae::GameObject* m_pPacman = nullptr;
};

