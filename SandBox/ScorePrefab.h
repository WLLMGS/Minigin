#pragma once
#include "GameObject.h"
#include "TextComponent.h"

class ScorePrefab : public dae::GameObject
{
public:
	ScorePrefab();
	~ScorePrefab();
	void IncreaseScore(int score);
private:
	int m_Score = 0;
	TextComponent* m_pTxtScore = nullptr;
};

