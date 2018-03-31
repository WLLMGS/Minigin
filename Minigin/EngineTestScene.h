#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "GameObject.h"
#include "GameActor.h"
#include "TextComponent.h"

class EngineTestScene : public dae::Scene
{
public:
	EngineTestScene();
	~EngineTestScene();
	
	virtual void Update(float elapsedSec) override;
private:
	TextComponent* m_pFpsComp = nullptr;
	GameActor* m_pTestObject = nullptr;
	int m_FpsCounter = 0;
	float m_FpsTimer = 0.0f;
};

