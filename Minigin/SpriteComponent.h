#pragma once
#include "BaseComponent.h"
#include <SDL.h>

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
		void SetAnimated(bool b);
		
		void SetAnimationParameters(int amountOfFrames, int framesPerSecond, float width, float height);
	private:
		void CalculateAnimations(float elapsedSec);
	private:
		SDL_Texture* m_pTexture = nullptr;
		float m_Width = GameSettings::TileSize;
		float m_Height  = GameSettings::TileSize;

		//animation
		bool m_IsAnimated = false;
		int m_AmountOfFrames = 0;
		int m_CurrentFrame = 0;
		float m_TileWidth = 0;
		float m_TileHeight = 0;
		float m_AnimationTimer = 0.0f;
		int m_FramesPerSecond = 0;
	};
}


