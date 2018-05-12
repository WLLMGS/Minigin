#pragma once
#include "GameObject.h"

class FpsCounterPrefab : public dae::GameObject
{
public:
	FpsCounterPrefab();
	~FpsCounterPrefab();
	virtual void Update(float elapsedSec) override;
private:
	float m_FpsTimer = 0.0f;
	int m_FpsCounter = 0;
};

