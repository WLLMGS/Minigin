#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "GameObject.h"

TextComponent::TextComponent(dae::FontName fontName,const SDL_Color& color,  const string& text)
{
	m_pFont = dae::ResourceManager::GetInstance().RequestFont(fontName);
	m_Color = color;
	SetText(text);
}

TextComponent::~TextComponent()
{
	//no need to clear font -> resource manager does it
	SDL_DestroyTexture(m_pTexture);
}

void TextComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void TextComponent::Render()
{
	dae::Renderer::GetInstance().RenderTexture(m_pTexture, gameObject->Transform()->GetPosition().x, gameObject->Transform()->GetPosition().y);
}

void TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}

void TextComponent::SetText(const string& text)
{
	//const SDL_Color color = { 255,0,0 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), text.c_str(), m_Color);
	if (surf == nullptr) {
		std::stringstream ss; ss << "Render text failed: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr) {
		std::stringstream ss; ss << "Create text texture from surface failed: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}
	SDL_FreeSurface(surf);
	//mTexture = std::make_shared<Texture2D>(texture);
	m_pTexture = texture;
}
