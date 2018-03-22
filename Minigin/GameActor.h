#pragma once
#include "GameObject.h"

enum Direction
{
	Right = 0,
	Left = 1,
	Up = 2,
	Down = 3
};

class GameActor : public dae::GameObject
{
public:
	GameActor();
	~GameActor();
	virtual void Update(float elapsedSec) override;
	virtual void SetDirection(const Direction direction);
protected:
	Direction m_Direction = Direction(0);
	float m_Speed = 300.0f;

private:
	void Move(float elapsedSec);
};

