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

void GameActor::Move(float elapsedSec)
{
	elapsedSec /= 1000.0f;
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


