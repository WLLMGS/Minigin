#pragma once
#include "Scene.h"
#include "ButtonPrefab.h"

class MainMenu : public dae::Scene
{
public:
	MainMenu();
	~MainMenu();
	virtual void Update(float elapsedSec) override;

private:
	

	vector<ButtonPrefab*> m_pButtons;
private:
	void InitButtons();

	float m_CoolDown = 0.2f;
};

