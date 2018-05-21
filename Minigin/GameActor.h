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
	Direction GetDirection() const;
	void SetSpawnPosition(float x, float y);
	glm::vec3 GetSpawnPosition() const;
protected:
	Direction m_Direction = Direction(0);
	float m_Speed = 300.0f;
	void Move(float elapsedSec);
	glm::vec3 m_SpawnPosition;
};

