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
	UNREFERENCED_PARAMETER(elapsedSec);
}

void dae::SpriteComponent::Render()
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_pGameObject->Transform()->GetPosition().x
		, m_pGameObject->Transform()->GetPosition().y
		, m_Width * m_pGameObject->Transform()->GetScale().x
		, m_Height * m_pGameObject->Transform()->GetScale().y
		, m_pGameObject->Transform()->GetAngle());
}


