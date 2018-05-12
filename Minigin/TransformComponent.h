#pragma once
#include "BaseComponent.h"
#include "Transform.h"
namespace dae
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent();
		~TransformComponent();
		virtual void Update(float elapsedSec) override;
		virtual void Render() override;

		glm::vec3 GetPosition() const;
		glm::vec3 GetScale() const;
		float GetAngle() const;
		void Translate(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void SetRotation(const float angle);
		void SetGameObject(GameObject* obj);
		void SetPosition(float x, float y);

	private:
		
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		float m_Angle = 0.0f;
	};
}
