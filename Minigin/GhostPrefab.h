#pragma once
#include "GameActor.h"
#include "LevelLoader.h"

class GhostPrefab : public GameActor
{
public:
	GhostPrefab();
	~GhostPrefab();
	virtual void Update(float elapsedSec) override;
private:
	static GameObject* m_pPlayer;
	static vector<dae::GridCell*> m_pGrid;

	const float m_Speed = 75.0f;
private:
	void CalculateMovement(float elapsedSec);

	const float m_Cooldown = 0.5f;
	float m_MoveCooldown = 0.5f;
};



