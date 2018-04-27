#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Logger.h"

ColliderComponent::ColliderComponent(bool isDynamic):
	m_IsDyamic(isDynamic)
{}

void ColliderComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
	auto transform = m_pGameObject->Transform();

	m_PosX = transform->GetPosition().x;
	m_PosY = transform->GetPosition().y;
	m_Width = GameSettings::TileSize * transform->GetScale().x;
	m_Height = GameSettings::TileSize * transform->GetScale().y;
}

void ColliderComponent::Render()
{
	#ifdef DEBUG
	dae::Renderer::GetInstance().RenderFillRectangle(m_PosX, m_PosY, m_Width, m_Height);
	#endif

}

bool ColliderComponent::CheckCollision(ColliderComponent* other)
{		
	
	float deltaX = other->m_PosX - m_PosX;
	float deltaY = other->m_PosY - m_PosY;

	float otherHalfWidth = other->m_Width / 2.0f;
	float otherHalfHeight = other->m_Height / 2.0f;

	float halfWidth = m_Width / 2.0f;
	float halfHeight = m_Height / 2.0f;

	//point where rects collide
	float intersectX = abs(deltaX) - (otherHalfWidth + halfWidth);
	float intersectY = abs(deltaY) - (otherHalfHeight + halfHeight);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		if (intersectX > intersectY)
		{
			//return true if they are both dynamic
			if(IsDynamic() && other->IsDynamic())
			{
				return true;
			}

			if (deltaX > 0.0f)
			{
				Move(intersectX, 0.0f);
			}
			else
			{
				Move(-intersectX, 0.0f);
			}
		}
		else
		{
			if(deltaY > 0.0f)
			{
				Move(0.0f, intersectY);
			}
			else
			{
				Move(0.0f, -intersectY);
			}
		}

		return true;
	}
	
	return false;
}

bool ColliderComponent::IsDynamic()
{
	return m_IsDyamic;
}

void ColliderComponent::Move(float x, float y)
{
	m_pGameObject->Transform()->Translate(x, y, 0);
}
