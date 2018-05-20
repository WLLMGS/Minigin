#pragma once
#include "Scene.h"
#include "ButtonPrefab.h"

class GameOverScene : public dae::Scene
{
public:
	GameOverScene();
	~GameOverScene();
	virtual void Update(float elapsedSec) override;
private:
	vector<ButtonPrefab*> m_pButtons;

	void InitButtons();

	float m_CoolDown = 0.2f;
};

