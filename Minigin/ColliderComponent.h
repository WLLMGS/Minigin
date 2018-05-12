#pragma once
#include "BaseComponent.h"
#include <glm/detail/type_vec.hpp>

class ColliderComponent : public dae::BaseComponent
{
public:
	ColliderComponent(bool isDynamic = true, float width = 32.0f, float height = 32.0f);
	~ColliderComponent() = default;
	virtual void Update(float elapsedSec) override;
	virtual void Render() override;
	bool CheckCollision(ColliderComponent* other);
	bool CheckCollisionWithMass(ColliderComponent* other);
	bool CheckTrigger(ColliderComponent* other);
	bool IsDynamic();
	void Move(float x, float y);
	void SetCollisionGroup(int id);
	int GetCollisionGroup();
	void SetCollisionIgnoreGroup(int id);
	int GetCollisionIgnoreGroup();

	void SetOffset(float xOffset, float yOffset);
	void SetDimensions(float width, float height);
	bool IsTrigger();
	void SetTrigger(bool trigger);


private:
	bool m_IsDyamic = true;
	bool m_IsTrigger = false;

	float m_PosX;
	float m_PosY;
	float m_Width;
	float m_Height;

	float m_ScaledWidth = 0.0f;
	float m_ScaledHeight = 0.0f;

	float m_OffsetX = 0.0f;
	float m_OffsetY = 0.0f;

	int m_CollisionGroup = 1;
	int m_IgnoreGroup = 0;
};

