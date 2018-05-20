#include "stdafx.h"
#include "ScorePrefab.h"
#include "TextComponent.h"
#include <string>


ScorePrefab::ScorePrefab()
{
	m_pTxtScore = new TextComponent(dae::FontName::DEFAULT, { 255,0,0,255 }, "Score: ");
	AddComponent(m_pTxtScore);

	SetName("Score");
}


ScorePrefab::~ScorePrefab()
{
}

void ScorePrefab::IncreaseScore(int score)
{
	m_Score += score;
	m_pTxtScore->SetText("Score: " + to_string(m_Score));
}
