#include "MiniginPCH.h"
#include "GameActor.h"


GameActor::GameActor()
{
}


GameActor::~GameActor()
{
}



void GameActor::Update(float elapsedSec)
{
	Move(elapsedSec);
}


void GameActor::SetDirection(const Direction direction)
{
	m_Direction = direction;
}

float GameActor::GetSpeed() const
{
	return m_Speed;
}

Direction GameActor::GetDirection() const
{
	return m_Direction;
}

void GameActor::SetSpawnPosition(float x, float y)
{
	m_SpawnPosition.x = x;
	m_SpawnPosition.y = y;
}

glm::vec3 GameActor::GetSpawnPosition() const
{
	return m_SpawnPosition;
}

void GameActor::Move(float elapsedSec)
{
	
	switch(m_Direction)
	{
	case Right:
		Transform()->Translate((m_Speed * elapsedSec), 0, 0);
		break;
	case Left:
		Transform()->Translate(-(m_Speed * elapsedSec), 0, 0);
		break;
	case Up:
		Transform()->Translate(0,-(m_Speed * elapsedSec), 0);
		break;
	case Down:
		Transform()->Translate(0, (m_Speed * elapsedSec), 0);
		break;
	}
}


