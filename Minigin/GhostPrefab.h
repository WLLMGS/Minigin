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

private:
	void CalculateMovement(float elapsedSec);
};



