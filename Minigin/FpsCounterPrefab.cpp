#include "MiniginPCH.h"
#include "FpsCounterPrefab.h"
#include "TextComponent.h"
#include "Logger.h"


FpsCounterPrefab::FpsCounterPrefab()
{
	AddComponent(new TextComponent(dae::FontName::DEFAULT, { 255,0,0,255 }, "FPS: "));
}

FpsCounterPrefab::~FpsCounterPrefab()
{
}

void FpsCounterPrefab::Update(float elapsedSec)
{
	m_FpsTimer += elapsedSec;
	++m_FpsCounter;

	if(m_FpsTimer >= 1.0f)
	{
		GetComponent<TextComponent>()->SetText("FPS: " + to_string(m_FpsCounter));
		m_FpsCounter = 0;
		m_FpsTimer = 0.0f;
	}

}
