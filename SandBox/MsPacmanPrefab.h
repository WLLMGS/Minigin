#pragma once

#include "GameActor.h"

class MsPacmanPrefab : public GameActor
{
public:
	MsPacmanPrefab();
	~MsPacmanPrefab();
	virtual void Update(float elapsedSec) override;
	void OnTriggerEnter(ColliderComponent* other) override;
	virtual void OnCollisionEnter(ColliderComponent* other) override;
	void Movement();
private:
	const float m_Cooldown = 0.2f;
	float m_MoveCooldown = 0.2f;
	int m_Lives = 3;

};

