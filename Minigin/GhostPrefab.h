#pragma once
#include "GameActor.h"
#include "LevelLoader.h"

class GhostPrefab : public GameActor
{
public:
	enum State
	{
		Chasing = 0,
		Running = 1,
		Controlled = 2
	};
public:
	GhostPrefab();
	~GhostPrefab();
	virtual void Update(float elapsedSec) override;
	void SetControlled();
	
	State GetState() const;
	void SetState(State state);
private:
	GameObject* m_pPlayer;
	vector<dae::GridCell*> m_pGrid;

	const float m_Speed = 75.0f;
	const float m_Cooldown = 0.5f;
	float m_MoveCooldown = 0.5f;

	
	State m_State;

	const float m_ChaseTime = 10.0f;
	const float m_RunTime = 10.0f;
	float m_StateTimer = 10.0f;

	private:
	void CalculateMovement(float elapsedSec, float targetX, float targetY);
	void Movement();
	void HandleChasing(float elapsedSec);
	void HandleRunning(float elapsedSec);
	void HandleControlled(float elapsedSec);
	void HandleStateSwitching(float elapsedSec);

};



