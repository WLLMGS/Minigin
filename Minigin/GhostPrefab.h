#pragma once
#include "GameActor.h"
#include "LevelLoader.h"

class GhostPrefab : public GameActor
{
public:
	GhostPrefab();
	~GhostPrefab();
	virtual void Update(float elapsedSec) override;
	void SetControlled(bool controlled);
	bool IsControlled() const;
	
private:
	GameObject* m_pPlayer;
	vector<dae::GridCell*> m_pGrid;

	const float m_Speed = 75.0f;
	const float m_Cooldown = 0.5f;
	float m_MoveCooldown = 0.5f;

	bool m_IsControlled = false;

	private:
	void CalculateMovement(float elapsedSec);
	void Movement();
};



