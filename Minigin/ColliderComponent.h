#pragma once
#include "BaseComponent.h"
#include <glm/detail/type_vec.hpp>

class ColliderComponent : public dae::BaseComponent
{
public:
	ColliderComponent(bool isDynamic = true);
	~ColliderComponent() = default;
	virtual void Update(float elapsedSec) override;
	virtual void Render() override;
	bool CheckCollision(ColliderComponent* other);
	bool IsDynamic();
	void Move(float x, float y);
private:
	bool m_IsDyamic = true;

	float m_PosX;
	float m_PosY;
	float m_Width;
	float m_Height;

};

