#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform final
	{
		
	public:
		const glm::vec3 GetPosition() const { return m_Position; }
		const glm::vec3 GetScale() const { return m_Scale; }
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
	};
}
