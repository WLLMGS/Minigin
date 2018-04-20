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
	//Renderer::GetInstance().RenderTexture(m_pTexture, m_pGameObject->Transform()->GetPosition().x
	//	, m_pGameObject->Transform()->GetPosition().y
	//	, m_Width * m_pGameObject->Transform()->GetScale().x
	//	, m_Height * m_pGameObject->Transform()->GetScale().y
	//	, m_pGameObject->Transform()->GetAngle());

	if(m_IsAnimated)
	{
		Renderer::GetInstance().RenderTexture(m_pTexture, m_pGameObject->Transform()->GetPosition().x
			, m_pGameObject->Transform()->GetPosition().y
			, m_Width * m_pGameObject->Transform()->GetScale().x
			, m_Height * m_pGameObject->Transform()->GetScale().y
			, m_pGameObject->Transform()->GetAngle()
			, m_CurrentFrame * m_TileWidth
			, 0.0f,
			m_TileWidth,
			m_TileHeight);
	}
	else
	{
		Renderer::GetInstance().RenderTexture(m_pTexture, m_pGameObject->Transform()->GetPosition().x
			, m_pGameObject->Transform()->GetPosition().y
			, m_Width * m_pGameObject->Transform()->GetScale().x
			, m_Height * m_pGameObject->Transform()->GetScale().y
			, m_pGameObject->Transform()->GetAngle());
	}
}

void dae::SpriteComponent::SetAnimated(bool b)
{
	m_IsAnimated = b;
}

void dae::SpriteComponent::SetAnimationParameters(int amountOfFrames, int framesPerSecond, float width, float height)
{
	m_AmountOfFrames = amountOfFrames;
	m_FramesPerSecond = framesPerSecond;
	m_TileWidth = width;
	m_TileHeight = height;
	
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


