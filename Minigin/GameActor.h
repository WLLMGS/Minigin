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
	void Update(float elapsedSec);
	void SetDirection(const Direction direction);
	float GetSpeed() const;
protected:
	Direction m_Direction = Direction(0);
	float m_Speed = 300.0f;
	void Move(float elapsedSec);
};

