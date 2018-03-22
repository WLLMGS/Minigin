#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "GameObject.h"
#include "GameActor.h"

class EngineTestScene : public dae::Scene
{
public:
	EngineTestScene();
	~EngineTestScene();
	
	virtual void Update(float elapsedSec) override;
private:
	dae::TextObject* m_pTxtFpsCounter = nullptr;
	GameActor* m_pTestObject = nullptr;
	int m_FpsCounter = 0;
	float m_FpsTimer = 0.0f;
};

