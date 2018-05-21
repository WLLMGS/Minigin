#pragma once
#include "GameObject.h"
#include "GameActor.h"

class PacmanPrefab : public GameActor
{
public:
	PacmanPrefab();
	~PacmanPrefab() = default;
	virtual void Update(float elapsedSec) override;
	void OnTriggerEnter(ColliderComponent* other) override;
	virtual void OnCollisionEnter(ColliderComponent* other) override;
	void Movement();
private:
	const float m_Cooldown = 0.2f;
	float m_MoveCooldown = 0.2f;
	int m_Lives = 3;
};

