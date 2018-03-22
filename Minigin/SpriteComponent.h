#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent(int textureName);
		~SpriteComponent();
		virtual void Update(float elapsedSec) override;
		virtual void Render() override;

	private:
		Texture2D* m_pTexture = nullptr;
		float m_Width = 32.0f;
		float m_Height = 32.0f;
	};
}


