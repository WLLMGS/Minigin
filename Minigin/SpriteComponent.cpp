#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::SpriteComponent::SpriteComponent(int textureName)
{
	m_pTexture = ResourceManager::GetInstance().RequestTexture(TextureName(textureName));
}


dae::SpriteComponent::~SpriteComponent()
{
}

void dae::SpriteComponent::Update(float elapsedSec)
{
	if(m_IsAnimated) CalculateAnimations(elapsedSec);
}

void dae::SpriteComponent::Render()
{
	if(m_IsAnimated)
	{
		Renderer::GetInstance().RenderTexture(m_pTexture, gameObject->Transform()->GetPosition().x
			, gameObject->Transform()->GetPosition().y
			, m_Width * gameObject->Transform()->GetScale().x
			, m_Height * gameObject->Transform()->GetScale().y
			, gameObject->Transform()->GetAngle()
			, m_StartWidth + m_CurrentFrame * m_TileWidth
			, m_StartHeight,
			m_TileWidth,
			m_TileHeight,
			m_IsMirrored);
	}
	else
	{
		Renderer::GetInstance().RenderTexture(m_pTexture, gameObject->Transform()->GetPosition().x
			, gameObject->Transform()->GetPosition().y
			, m_Width * gameObject->Transform()->GetScale().x
			, m_Height * gameObject->Transform()->GetScale().y
			, gameObject->Transform()->GetAngle()
			,m_StartWidth
			,m_StartHeight
			,m_Width
			,m_Height
			, m_IsMirrored
			);
	}
}

void dae::SpriteComponent::SetAnimated(bool b)
{
	m_IsAnimated = b;
}

void dae::SpriteComponent::SetStartHeight(float height)
{
	m_StartHeight = height;
}

void dae::SpriteComponent::SetStartWidth(float width)
{
	m_StartWidth = width;
}

void dae::SpriteComponent::SetAnimationParameters(int amountOfFrames, int framesPerSecond, float width, float height)
{
	m_AmountOfFrames = amountOfFrames;
	m_FramesPerSecond = framesPerSecond;
	m_TileWidth = width;
	m_TileHeight = height;
	
}

void dae::SpriteComponent::SetTexture(int textureName)
{
	m_pTexture = ResourceManager::GetInstance().RequestTexture(TextureName(textureName));
}

void dae::SpriteComponent::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void dae::SpriteComponent::SetMirrored(bool mirrored)
{
	m_IsMirrored = mirrored;
}

void dae::SpriteComponent::CalculateAnimations(float elapsedSec)
{
	m_AnimationTimer += elapsedSec;

	if(m_AnimationTimer > (1.0f / m_FramesPerSecond))
	{
		m_AnimationTimer = 0.0f;
		++m_CurrentFrame;

		if(m_CurrentFrame > (m_AmountOfFrames - 1))
		{
			m_CurrentFrame = 0;
		}
	}
}


