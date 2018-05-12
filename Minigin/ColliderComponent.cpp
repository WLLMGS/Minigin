#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Logger.h"

ColliderComponent::ColliderComponent(bool isDynamic, float width, float height):
	m_IsDyamic(isDynamic),
	m_Width(width),
	m_Height(height)
{}

void ColliderComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
	auto transform = gameObject->Transform();

	m_PosX = transform->GetPosition().x + (m_OffsetX *transform->GetScale().x);
	m_PosY = transform->GetPosition().y + (m_OffsetY *transform->GetScale().y);
	m_ScaledWidth = m_Width * transform->GetScale().x;
	m_ScaledHeight = m_Height * transform->GetScale().y;

}

void ColliderComponent::Render()
{
	#ifdef DEBUG
	dae::Renderer::GetInstance().RenderFillRectangle(m_PosX, m_PosY, m_ScaledWidth, m_ScaledHeight);
	#endif

}

bool ColliderComponent::CheckCollision(ColliderComponent* other)
{		
	
	float deltaX = other->m_PosX - m_PosX;
	float deltaY = other->m_PosY - m_PosY;

	float otherHalfWidth = other->m_ScaledWidth / 2.0f;
	float otherHalfHeight = other->m_ScaledHeight / 2.0f;

	float halfWidth = m_ScaledWidth / 2.0f;
	float halfHeight = m_ScaledHeight / 2.0f;

	//point where rects collide
	float intersectX = abs(deltaX) - (otherHalfWidth + halfWidth);
	float intersectY = abs(deltaY) - (otherHalfHeight + halfHeight);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		if (intersectX > intersectY)
		{
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

bool ColliderComponent::CheckCollisionWithMass(ColliderComponent* other)
{
	float deltaX = other->m_PosX - m_PosX;
	float deltaY = other->m_PosY - m_PosY;

	float otherHalfWidth = other->m_ScaledWidth / 2.0f;
	float otherHalfHeight = other->m_ScaledHeight / 2.0f;

	float halfWidth = m_ScaledWidth / 2.0f;
	float halfHeight = m_ScaledHeight/ 2.0f;

	//point where rects collide
	float intersectX = abs(deltaX) - (otherHalfWidth + halfWidth);
	float intersectY = abs(deltaY) - (otherHalfHeight + halfHeight);

	float mass = gameObject->GetMass();
	float otherMass = other->GetGameObject()->GetMass();

	float tot = mass + otherMass;
	
	float push1 = otherMass / tot;
	float push2 = mass / tot;

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * push1, 0.0f);
				other->Move(-intersectX * push2, 0.0f);
			}
			else
			{
				Move(-intersectX * push1, 0.0f);
				other->Move(intersectX * push2, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * push1);
				other->Move(0.0f, -intersectY * push2);

			}
			else
			{
				Move(0.0f, -intersectY * push1);
				other->Move(0.0f, intersectY * push2);
			}
		}

		return true;
	}

	return false;
}

bool ColliderComponent::CheckTrigger(ColliderComponent* other)
{
	float deltaX = other->m_PosX - m_PosX;
	float deltaY = other->m_PosY - m_PosY;

	float otherHalfWidth = other->m_ScaledWidth / 2.0f;
	float otherHalfHeight = other->m_ScaledHeight / 2.0f;

	float halfWidth = m_ScaledWidth / 2.0f;
	float halfHeight = m_ScaledHeight / 2.0f;

	//point where rects collide
	float intersectX = abs(deltaX) - (otherHalfWidth + halfWidth);
	float intersectY = abs(deltaY) - (otherHalfHeight + halfHeight);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
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
	gameObject->Transform()->Translate(x, y, 0);
}

void ColliderComponent::SetCollisionGroup(int id)
{
	m_CollisionGroup = id;
}

int ColliderComponent::GetCollisionGroup()
{
	return m_CollisionGroup;
}

void ColliderComponent::SetCollisionIgnoreGroup(int id)
{
	m_IgnoreGroup = id;
}

int ColliderComponent::GetCollisionIgnoreGroup()
{
	return m_IgnoreGroup;
}

void ColliderComponent::SetOffset(float xOffset, float yOffset)
{
	m_OffsetX = xOffset;
	m_OffsetY = yOffset;
}

void ColliderComponent::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

bool ColliderComponent::IsTrigger()
{
	return m_IsTrigger;
}

void ColliderComponent::SetTrigger(bool trigger)
{
	m_IsTrigger = trigger;
}
